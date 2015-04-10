<?hh //strict

namespace Krona\HPA\Hydrator\Converter;

use Krona\HPA\Entity\EntityInterface;
use ReflectionProperty;

interface AbstractConverterInterface extends ConverterInterface
{
    public function canConvert(ReflectionProperty $property):bool;
}
