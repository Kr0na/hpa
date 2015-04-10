<?hh //strict

namespace Krona\HPATest\Hydrator;

use Krona\HPA\Hydrator\ObjectHydrator;
use Krona\HPATest\Entity\User;
use Krona\HPATest\Entity\Status;
use Krona\HPATest\TestTrait;

class ObjectHydratorTest
{
    use TestTrait;

    public function testRawHydration():void
    {
        $hydrator = $this->getEntityManager()->getObjectHydrator();
        $user = new User();
        $hydrator->hydrateRaw($user, Map {
            'id' => '1'
        });
        $this
            ->assertTrue($user->getId() === 1)
            ->assertTrue(is_null($user->getStatus()))
        ;
    }

    public function testRawInner():void
    {
        $hydrator = $this->getEntityManager()->getObjectHydrator();
        $user = new User();
        $hydrator->hydrateRaw($user, Map {
            'status' => '1'
        });

        $status = $user->getStatus();

        $this
            ->assertTrue($status instanceof Status)
            ->assertTrue($status && $status->getId() === 1)
        ;
    }
}
