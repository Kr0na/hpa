<?hh //strict

namespace Krona\HPATest\Connection;

use AsyncMysqlConnection;
use Krona\HPATest\TestTrait;

class ConnectionPoolTest
{
    use TestTrait;

    public async function testConnection():Awaitable<void>
    {
        $pool = $this->getEntityManager()->getConnectionPool();
        for ($i = 0; $i < 2; $i++) {
            $connection = await $pool->getConnection();
            $this->assertTrue($connection instanceof AsyncMysqlConnection);
        }
    }
}
