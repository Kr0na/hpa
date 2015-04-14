<?hh
namespace Krona\HPATest;
require_once __DIR__ . '/../vendor/autoload.php';

// use Krona\HPATest\Hydrator\ObjectHydratorTest;
use Krona\HPATest\Connection\ConnectionPoolTest;

// $hydratorTest = new ObjectHydratorTest();
// $hydratorTest->run();
$connectionPoolTest = new ConnectionPoolTest();
$connectionPoolTest->run();
