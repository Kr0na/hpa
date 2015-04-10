<?hh //strict

namespace Krona\HPATest;

use Krona\HPA\EntityManager;
use Krona\HPATest\Configuration\ConfigurationManager;
use ReflectionClass;
use Exception;

trait TestTrait
{
    protected ?EntityManager $entityManager;
    protected Map<string, mixed> $fails = Map {};
    protected Map<string, mixed> $success = Map {};
    protected Map<string, Vector<bool>> $assertions = Map {};

    protected ?string $currentMethod;

    public function getEntityManager():EntityManager
    {
        if (is_null($this->entityManager)) {
            $this->entityManager = new EntityManager(new ConfigurationManager());
        }

        return $this->entityManager;
    }

    public function run():void
    {
        $reflection = new ReflectionClass($this);
        foreach($reflection->getMethods() as $method) {
            if (strpos($method->getName(), 'test') !== false) {
                $this->currentMethod = $method->getName();
                $assetions = Vector {};
                $this->assertions->add(Pair {$this->currentMethod, $assetions});
                try {
                    $method->invoke($this);
                } catch(Exception $e) {
                    $this->fails->add(Pair {$method->getName(), $e});
                    continue;
                }

                if ($assetions->linearSearch(false) !== -1) {
                    $this->fails->add(Pair {$method->getName(), false});
                    continue;
                }
                $this->success->add(Pair {$method->getName(), true});
            }
        }

        echo 'Test result for: ' . $reflection->getName() . PHP_EOL;
        echo 'Success: ' . $this->success->count() . PHP_EOL;
        echo 'Fails: ' . $this->fails->count() . PHP_EOL;

        foreach($this->fails as $method => $result)
        {
            echo 'Result of ' . $method . PHP_EOL;
            var_dump($result);
        }
    }

    public function assertTrue(bool $condition):this
    {
        if (is_null($this->currentMethod)) {
            throw new Exception('cannot assert from out test method');
        }
        $assertion = $this->assertions->at($this->currentMethod);
        $assertion->add($condition);

        return $this;
    }
}
