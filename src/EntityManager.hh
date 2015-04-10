<?hh //strict

namespace Krona\HPA;

use Krona\HPA\Mapper\EntityMapper;
use Krona\HPA\Mapper\MapperManager;

class EntityManager
{
    protected MapperManager $mapperManager;

    public function __construct()
    {
        $this->mapperManager = new MapperManager();
    }

    public function getMapper(string $entityClassName):EntityMapper
    {
        return $this->mapperManager->getMapper($entityClassName);
    }
}
