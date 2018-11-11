class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        string ret;
        size_t start_index = 0;
        size_t num_chars   = 0;
        auto bs = bitset<128>();
        
        auto check_if_longest = [&s, &ret](size_t start_index, size_t num_chars) {
            auto tmp = s.substr(start_index, num_chars);
            if (tmp.length() > ret.length()) {
                ret = tmp;
            }    
        };
        
        for (auto i = 0; i < s.length(); ++i) {
            auto ascii_value = static_cast<int>(s[i]);
            if (bs[ascii_value]) {
                check_if_longest(start_index, num_chars);
                
                auto last_index_of_found_char = s.find(s[i], start_index); 
                for (auto j = start_index; j < last_index_of_found_char; ++j) {
                    bs.reset(static_cast<int>(s[j]));
                }
                
                start_index = last_index_of_found_char + 1;
                num_chars = i - last_index_of_found_char;
            } else {
                ++num_chars;
                bs.set(ascii_value);
            }
        }
        
        check_if_longest(start_index, num_chars);
        
        return ret.length();
    }
};
