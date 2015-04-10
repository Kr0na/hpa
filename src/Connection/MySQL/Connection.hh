<?hh //strict

namespace Krona\HPA\Connection\MySQL;

use AsyncMysqlConnection;
use AsyncMysqlResult;

class Connection {
    protected bool $reusable = true;

    protected ?AsyncMysqlConnection $connection;

    protected ConnectionPool $pool;

    public function __construct(ConnectionPool $pool) {
        $this->pool = $pool;
    }

    public function query(string $query):Awaitable<AsyncMysqlResult> {
        $connection = $this->getPooledConnection()->getWaitHandle()->join();
        $wait = $connection->query($query);

        return $wait;
    }

    public async function getPooledConnection():Awaitable<AsyncMysqlConnection> {
        if ($this->connection) {
            return $this->connection;
        } else {
            return await $this->pool->getConnection();
        }
    }
}
