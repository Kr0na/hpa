<?hh //strict

namespace Krona\HPATest\Entity;

use Krona\HPA\Entity\EntityInterface;

class Status implements EntityInterface
{
    protected ?int $id;

    protected ?string $name;

    public function getId():?int {
        return $this->id;
    }
}
