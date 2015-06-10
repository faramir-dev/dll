//=======================================================================
// Copyright (c) 2014 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#ifndef DLL_PATCHES_LAYER_INL
#define DLL_PATCHES_LAYER_INL

namespace dll {

/*!
 * \brief Layer to cut images into patches.
 */
template<typename Desc>
struct patches_layer {
    using desc = Desc;

    static constexpr const std::size_t width = desc::width;
    static constexpr const std::size_t height = desc::height;
    static constexpr const std::size_t v_stride = desc::v_stride;
    static constexpr const std::size_t h_stride = desc::h_stride;

    using weight = double; //TODO Should be made configurable

    using input_one_t = etl::dyn_matrix<weight>;
    using output_one_t = std::vector<etl::dyn_matrix<weight>>;
    using input_t = std::vector<input_one_t>;
    using output_t = std::vector<output_one_t>;

    patches_layer() = default;

    static std::string to_short_string(){
        return "patches";
    }

    static void display(){
        std::cout << to_short_string() << std::endl;
    }

    //TODO Ideally, the dbn should guess if h_a/h_s are used or only h_a

    static void activate_one(const input_one_t& input, output_one_t& h_a){
        activate_one(input, h_a, h_a);
    }

    static void activate_one(const input_one_t& input, output_one_t& h_a, output_one_t& h_s){
        //TODO
    }

    static void activate_many(const input_t& input, output_t& h_a, output_t& h_s){
        for(std::size_t i = 0; i < input.size(); ++i){
            activate_one(input[i], h_a[i], h_s[i]);
        }
    }

    static void activate_many(const input_t& input, output_t& h_a){
        for(std::size_t i = 0; i < input.size(); ++i){
            activate_one(input[i], h_a[i]);
        }
    }

    template<typename Input>
    static output_t prepare_output(std::size_t samples){
        return output_t();
    }

    template<typename Input>
    static output_one_t prepare_one_output(){
        return output_one_t();
    }
};

//Allow odr-use of the constexpr static members

template<typename Desc>
const std::size_t patches_layer<Desc>::width;

template<typename Desc>
const std::size_t patches_layer<Desc>::height;

template<typename Desc>
const std::size_t patches_layer<Desc>::v_stride;

template<typename Desc>
const std::size_t patches_layer<Desc>::h_stride;

} //end of dll namespace

#endif