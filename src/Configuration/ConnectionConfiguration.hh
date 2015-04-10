<?hh //strict

namespace Krona\HPA\Configuration;

class ConnectionConfiguration
{
    protected string $host;

    protected int $port = 3306;

    protected string $dbname;

    protected string $username = "";

    protected string $password = "";

    public function __construct(string $host, string $dbname, string $username = "", string $password = "", int $port = 3306)
    {
        $this->host = $host;
        $this->dbname = $dbname;
        $this->username = $username;
        $this->password = $password;
        $this->port = $port;
    }

    public function getHost():string
    {
        return $this->host;
    }

    public function getPort():int
    {
        return $this->port;
    }

    public function getDbname():string
    {
        return $this->dbname;
    }

    public function getUsername():string
    {
        return $this->username;
    }

    public function getPassword():string
    {
        return $this->password;
    }
}
