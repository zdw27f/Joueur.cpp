// ${header}
// ${obj['description']}
<% obj_key_name = underscore(obj_key).capitalize() %>
<%include file="functions.noCreer" />
#include "${underscore(obj_key)}.hpp"
#include "../../joueur/src/base_ai.hpp"
#include "../../joueur/src/any.hpp"
#include "../../joueur/src/exceptions.hpp"
#include "../../joueur/src/delta.hpp"
% for game_obj_key in sort_dict_keys(game_objs):
#include "${underscore(game_obj_key)}.hpp"
% endfor
#include "impl/${underscore(game_name)}.hpp"

#include <type_traits>

namespace cpp_client
{

namespace ${underscore(game_name)}
{

} // ${underscore(game_name)}

} // cpp_client