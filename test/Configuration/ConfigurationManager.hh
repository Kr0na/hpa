<?hh //strict

namespace Krona\HPATest\Configuration;

use Krona\HPA\Configuration\ConnectionConfiguration;
use Krona\HPA\Service\ConfigurationManager as BaseConfigurationManager;

class ConfigurationManager extends BaseConfigurationManager
{
    public function getConnectionConfiguration():ConnectionConfiguration
    {
        return new ConnectionConfiguration('localhost', 'test', 'root', 'freeware');
    }
}
