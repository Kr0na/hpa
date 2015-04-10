<?hh //strict

namespace Krona\HPA\Connection\MySQL;

use AsyncMysqlConnection;
use AsyncMysqlClient;
use Exception;
use Krona\HPA\Configuration\ConnectionConfiguration;

class ConnectionPool {
    protected ConnectionConfiguration $configuration;
    protected Vector<AsyncMysqlConnection> $connections = Vector {};

    public function __construct(ConnectionConfiguration $configuration) {
        $this->configuration = $configuration;
    }

    public async function getConnection():Awaitable<AsyncMysqlConnection> {
        try {
            return $this->connections->pop();
        } catch(Exception $e) {
            return await $this->connect();
        }
    }

    public async function connect():Awaitable<AsyncMysqlConnection> {
        return await AsyncMysqlClient::connect(
            $this->configuration->getHost(),
            $this->configuration->getPort(),
            $this->configuration->getDbname(),
            $this->configuration->getUsername(),
            $this->configuration->getPassword(),
        );
    }

    public function free(AsyncMysqlConnection $connection):void {
        $this->connections->add($connection);
    }
}
