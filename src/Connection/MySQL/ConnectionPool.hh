<?hh //strict

namespace Krona\HPA\Connection\MySQL;

use AsyncMysqlConnection;
use AsyncMysqlConnectionPool;
use AsyncMysqlClient;
use Exception;
use Krona\HPA\Configuration\ConnectionConfiguration;

class ConnectionPool {
    protected ConnectionConfiguration $configuration;
    protected AsyncMysqlConnectionPool $pool;

    public function __construct(ConnectionConfiguration $configuration) {
        $this->configuration = $configuration;
        $this->pool = new AsyncMysqlConnectionPool([]);
    }

    public async function getConnection():Awaitable<AsyncMysqlConnection> {
        return await $this->pool->connect(
            $this->configuration->getHost(),
            $this->configuration->getPort(),
            $this->configuration->getDbname(),
            $this->configuration->getUsername(),
            $this->configuration->getPassword()
        );
    }
}
