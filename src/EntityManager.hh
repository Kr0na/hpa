<?hh //strict

namespace Krona\HPA;

use Krona\HPA\Connection\MySQL\ConnectionPool;
use Krona\HPA\Hydrator\ObjectHydrator;
use Krona\HPA\Mapper\EntityMapper;
use Krona\HPA\Mapper\MapperManager;
use Krona\HPA\Service\ConfigurationProviderInterface;

class EntityManager
{
    protected ConfigurationProviderInterface $configurationManager;

    protected ConnectionPool $connectionPool;

    protected ObjectHydrator $objectHydrator;

    protected MapperManager $mapperManager;

    public function __construct(ConfigurationProviderInterface $configurationManager)
    {
        $this->configurationManager = $configurationManager;
        $this->connectionPool = new ConnectionPool($configurationManager->getConnectionConfiguration());
        $this->objectHydrator = new ObjectHydrator($configurationManager->getHydrationConfiguration());
        $this->mapperManager = new MapperManager();
    }

    public function getObjectHydrator():ObjectHydrator
    {
        return $this->objectHydrator;
    }

    public function getConnectionPool():ConnectionPool
    {
        return $this->connectionPool;
    }

    public function getMapper(string $entityClassName):EntityMapper
    {
        return $this->mapperManager->getMapper($entityClassName);
    }
}
