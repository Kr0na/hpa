<?hh //strict

namespace Krona\HPA\Connection\MySQL;

use AsyncMysqlConnection;
use AsyncMysqlConnectionPool;
use Krona\HPA\Configuration\ConnectionConfiguration;

class ConnectionManager
{
    protected ConnectionConfiguration $configuration;
    protected ConnectionPool $pool;

    public function __construct(ConnectionConfiguration $configuration)
    {
        $this->configuration = $configuration;
        $this->pool = new ConnectionPool($configuration);
    }

    public function getConnection(bool $reusable = false):Connection
    {
        $connection = new Connection($this->pool);
        if ($reusable) {

        }

        return $connection;
    }
}
