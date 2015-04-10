<?hh //strict

namespace Krona\HPA\Service;

use Krona\HPA\Configuration\ConnectionConfiguration;
use Krona\HPA\Configuration\HydrationConfiguration;

interface ConfigurationProviderInterface
{
    public function getConnectionConfiguration():ConnectionConfiguration;

    public function getHydrationConfiguration():HydrationConfiguration;
}
