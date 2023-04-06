#include <stdexcept>
#include <iostream>
#include "Horologe.h"

//////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////

DatetimeComponent* Horologe::get_component_by_idx(int idx) const
{
        // Check if idx is in range of Time's n_components
        if (idx < 0 || idx > component_hierarchy.size()-1)
        {
                throw std::invalid_argument(&"idx must be between 0 and " [component_hierarchy.size()-1]);
        }
        return component_hierarchy[idx];

}
