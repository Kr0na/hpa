<?hh //strict

namespace Krona\HPA\Hydrator\Converter;

use Krona\HPA\Entity\EntityInterface;
use ReflectionProperty;

interface ConverterInterface
{
    public function convert(ReflectionProperty $property, EntityInterface $entity, string $value):void;
}
