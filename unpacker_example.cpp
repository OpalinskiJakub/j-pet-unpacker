#include "unpacker.hpp"
#include <bitset>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

int main(int argc, char **argv)
{
    std::ifstream fp( "/home/jakub/CLionProjects/j-pet-unpacker/dabc_24024142936.hld", std::ios::in | std::ios::binary );

    unpacker::meta_t meta_data;
    std::unordered_map<unsigned int, std::vector<unpacker::hit_t>> original_data;
    std::unordered_map<unsigned int, std::vector<unpacker::hit_t>> filtered_data;
    std::unordered_map<unsigned int, std::vector<unpacker::sigmat_t>> preproc_data;
    std::unordered_map<unsigned int, std::string> paths_to_tdc_calib;
    
    /*for (int i=1; i<=4; i++)
        for (int j=1; j<=12; j++)
        {
            unsigned int id = i << 4 | j;
            std::stringstream ss;
            ss << std::hex << id;
            std::string s_id;
            ss >> s_id;    
            // std::string path_to_calib = "/storage/tdc_calib/A" + s_id + "0_tdc_calib.txt";
            std::string path_to_calib = "/home/baciek/Documents/djpet_software/pyhld/calib/0xa" + s_id + "0_calib.txt";
            paths_to_tdc_calib[ 0xa<<12 | i<<8 | j<< 4 ] = path_to_calib;
        } 

    unpacker::load_tdc_calib(paths_to_tdc_calib);
*/

    uint32_t previous_counter_number;
    bool first_iteration = true;

    int total_differences = 0;
    int differences_over_one = 0;
    u_int32_t max_difference = 1;
    int decreasing_count = 0;

    int succ = 1;
    while( succ ) {

        succ = unpacker::get_time_window( meta_data, original_data, filtered_data, preproc_data, fp );

        uint32_t counter_number = unpacker::fix_raw_trigger(meta_data.raw_trigger_id);

        if(first_iteration){
          previous_counter_number = counter_number;
          first_iteration = false;
        }else{

          uint32_t difference = counter_number - previous_counter_number;

          total_differences++;

          if(difference !=1){
            differences_over_one++;
          }
          if(difference>max_difference){
            max_difference=difference;
          }
          if (counter_number < previous_counter_number) {
            decreasing_count++;
          }

          previous_counter_number=counter_number;
        }

    }

    double percent_over_one = (double) differences_over_one/total_differences * 100;
    std::cout << "Percentage of differences greater than 1: " << percent_over_one << "%" << std::endl;
    std::cout<<"Max difference:"<<max_difference <<std::endl;
    std::cout << "Number of decreasing counters: " << decreasing_count << std::endl;



    return 0;
}
//std::cout<<std::bitset<32>(combined_bits)<<std::endl;