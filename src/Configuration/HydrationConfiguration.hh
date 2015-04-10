<?hh //strict

namespace Krona\HPA\Configuration;

use Krona\HPA\Exception\KronaException;
use Krona\HPA\Hydrator\Converter\ConverterInterface;
use Krona\HPA\Hydrator\Converter\AbstractConverterInterface;
use ReflectionProperty;

class HydrationConfiguration
{
    protected Map<string, ConverterInterface> $converters = Map {};
    protected Map<string, AbstractConverterInterface> $abstractConverters = Map {};

    public function __construct(Map<string, ConverterInterface> $converters = Map {})
    {
        foreach($converters as $key => $converter) {
            $this->addConverter($key, $converter);
        }
    }

    public function getConverter(ReflectionProperty $property):ConverterInterface
    {
        $type = str_replace('?', '', $property->getTypeText());
        $converter = $this->converters->get($type);

        if ($converter) {
            return $converter;
        } else {
            return $this->findAbstractConverter($property);
        }
    }

    protected function findAbstractConverter(ReflectionProperty $property):AbstractConverterInterface
    {
        foreach($this->abstractConverters as $converter) {
            if ($converter->canConvert($property)) {
                return $converter;
            }
        }

        throw new KronaException(sprintf('Converter for type %s not found', str_replace('?', '', $property->getTypeText())));
    }

    public function addConverter(string $type, ConverterInterface $converter):this
    {
        if ($converter instanceof AbstractConverterInterface) {
            $this->abstractConverters->add(Pair {$type, $converter});
        } else {
            $this->converters->add(Pair {$type, $converter});
        }

        return $this;
    }
}
