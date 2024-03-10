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
    int succ = 1;
    while( succ ) {
        succ = unpacker::get_time_window( meta_data, original_data, filtered_data, preproc_data, fp );
        uint32_t combined_bits = unpacker::fix_raw_trigger(meta_data.raw_trigger_id);
        std::cout<<std::bitset<32>(combined_bits)<<std::endl;
        /* print original data */
        //printf("{%02x\n", (meta_data.raw_trigger_id << 8) | (meta_data.raw_trigger_id >> 24));
        //printf("{%02x\n", meta_data.tw_trigger_id >> 16);
         //for (auto const &pair: original_data)
         {
             //printf("{%02x\n", pair.first);


             /*for (auto const &val : pair.second)
             {
                 printf("\t%02x (%d, %d, %.0f),\n", val.sample,
                                                   val.is_falling_edge,
                                                   val.channel_id,
                                                   val.time);
             }*/
            
             //printf("}\n");
         }

        // /* print filtered data */
         /*
         for (auto const &pair: filtered_data)
         {
             printf("{%02x\n", pair.first);

             for (auto const &val : pair.second)
             {
                 printf("\t%02x (%d, %d, %.0f),\n", val.sample,
                                                   val.is_falling_edge,
                                                   val.channel_id,
                                                   val.time);
             }
            
             printf("}\n");
         }
*/
        // /* print preproc data */
         /*
         for (auto const &pair: preproc_data)
         {
             printf("{%02x\n", pair.first);

             for (auto const &val : pair.second)
             {
                 printf("\t(%.0f %.0f %d %d),\n", val.lead_time,
                                             val.tot_time,
                                             val.strip_id,
                                             val.multiplicity);
             }

             printf("}\n");
         }

*/    //getchar();

    }


    return 0;
}
