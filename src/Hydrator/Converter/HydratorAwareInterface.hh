<?hh //strict

namespace Krona\HPA\Hydrator\Converter;

use Krona\HPA\Hydrator\ObjectHydrator;

interface HydratorAwareInterface
{
    public function setHydrator(ObjectHydrator $hydrator):void;
}
