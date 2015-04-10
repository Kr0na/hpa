<?hh
namespace Krona\HPATest;
require_once __DIR__ . '/../vendor/autoload.php';

use Krona\HPATest\Hydrator\ObjectHydratorTest;

$hydratorTest = new ObjectHydratorTest();
$hydratorTest->run();
