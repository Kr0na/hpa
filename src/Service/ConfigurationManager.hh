<?hh //strict

namespace Krona\HPA\Service;

use Krona\HPA\Configuration\ConnectionConfiguration;
use Krona\HPA\Configuration\HydrationConfiguration;
use Krona\HPA\Hydrator\Converter\EntityConverter;

class ConfigurationManager implements ConfigurationProviderInterface
{
    public function getConnectionConfiguration():ConnectionConfiguration
    {
        return new ConnectionConfiguration('localhost', 'dbname', 'user', 'password');
    }

    public function getHydrationConfiguration():HydrationConfiguration
    {
        return new HydrationConfiguration(
            Map {
                'entity' => new EntityConverter()
            }
        );
    }
}
