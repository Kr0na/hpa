<?hh //strict

namespace Krona\HPA\Hydrator;

use AsyncMysqlRow;
use Krona\HPA\Entity\EntityInterface;
use Krona\HPA\Configuration\HydrationConfiguration;
use Krona\HPA\Hydrator\Converter\ConverterInterface;
use Krona\HPA\Hydrator\Converter\HydratorAwareInterface;
use ReflectionClass;
use ReflectionProperty;

class ObjectHydrator
{
    protected HydrationConfiguration $configuration;

    public function __construct(HydrationConfiguration $configuration)
    {
        $this->configuration = $configuration;
    }

    public function hydrateRaw(EntityInterface $entity, Map<string, string> $data):void
    {
        $reflection = new ReflectionClass($entity);
        foreach($reflection->getProperties() as $property) {
            $property->setAccessible(true);
            $type = $this->normalizeType($property->getTypeText());
            if ($data->containsKey($property->getName())) {
                $value = $data->get($property->getName());
                switch($type) {
                    case 'int':
                        $property->setValue($entity, (int)$value);
                        break;
                    case 'double':
                    case 'float':
                        $property->setValue($entity, (float)$value);
                        break;
                    case 'string':
                        $property->setValue($entity, $value);
                        break;
                    case 'bool':
                        $property->setValue($entity, $value);
                        break;
                    default:
                        $this->hydrateValue($property, $entity, (string)$value);
                }
            }
        }
    }

    public function hydrate(EntityInterface $entity, AsyncMysqlRow $row):void {
        $reflection = new ReflectionClass($entity);
        foreach($reflection->getProperties() as $property) {
            $property->setAccessible(true);
            $type = $this->normalizeType($property->getTypeText());
            if (!$row->isNull($property->getName())) {
                switch($type) {
                    case 'int':
                        $property->setValue($entity, $row->getFieldAsInt($property->getName()));
                        break;
                    case 'double':
                    case 'float':
                        $property->setValue($entity, $row->getFieldAsDouble($property->getName()));
                        break;
                    case 'string':
                        $property->setValue($entity, $row->getFieldAsString($property->getName()));
                        break;
                    case 'bool':
                        $property->setValue($entity, !!$row->getFieldAsInt($property->getName()));
                        break;
                    default:
                        $this->hydrateValue($property, $entity, $row->getFieldAsString($property->getName()));
                }
            }
        }
    }

    protected function hydrateValue(ReflectionProperty $property, EntityInterface $entity, string $value):void
    {
        $converter = $this->configuration->getConverter($property);
        $this->initConverter($converter);
        $converter->convert($property, $entity, $value);
    }

    protected function initConverter(ConverterInterface $converter):void
    {
        if ($converter instanceof HydratorAwareInterface) {
            $converter->setHydrator($this);
        }
    }

    protected function normalizeType(string $type):string {
        $type = str_replace('?', '', $type);
        if (strpos($type, 'HH') === 0) {
            return str_replace('HH\\', '', $type);
        } else {
            return $type;
        }
    }
}
