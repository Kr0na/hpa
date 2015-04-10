<?hh //strict

namespace Krona\HPA\Mapper;

class MapperManager
{
    protected Map<string, EntityMapper> $mappers;

    public function __construct()
    {
        $this->mappers = Map {};
    }

    public function getMapper(string $entityClassName):EntityMapper
    {
        $mapper = $this->mappers->get($entityClassName);
        if ($mapper) {
            return $mapper;
        } else {
            $mapper = new EntityMapper();
            $this->mappers->add(Pair {$entityClassName, $mapper});
            return $mapper;
        }
    }
}
