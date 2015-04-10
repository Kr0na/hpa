<?hh //strict

namespace Krona\HPATest\Entity;

use Krona\HPA\Entity\EntityInterface;

class User implements EntityInterface
{
    protected ?int $id;

    protected ?string $login;

    protected ?string $password;

    protected ?bool $isActive;

    protected ?Status $status;

    public function getId():?int
    {
        return $this->id;
    }

    public function getStatus():?Status
    {
        return $this->status;
    }
}
