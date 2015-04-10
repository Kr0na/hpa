<?hh //strict

namespace Krona\HPA\Hydrator\Converter;

use Krona\HPA\Entity\EntityInterface;
use Krona\HPA\Hydrator\ObjectHydrator;
use ReflectionClass;
use ReflectionProperty;

class EntityConverter implements AbstractConverterInterface, HydratorAwareInterface
{
    protected ?ObjectHydrator $hydrator;

    public function canConvert(ReflectionProperty $property):bool
    {
        $reflection = new ReflectionClass(str_replace('?', '', $property->getTypeText()));
        return $reflection->implementsInterface(EntityInterface::class);
    }

    public function convert(ReflectionProperty $property, EntityInterface $entity, string $value):void
    {
        $reflection = new ReflectionClass(str_replace('?', '', $property->getTypeText()));
        $target = $reflection->newInstanceArgs();
        if ($this->hydrator) {
            $this->hydrator->hydrateRaw(
                $target,
                Map {
                    'id' => $value
                }
            );
        }

        $property->setValue($entity, $target);
    }

    public function setHydrator(ObjectHydrator $hydrator):void
    {
        $this->hydrator = $hydrator;
    }
}
