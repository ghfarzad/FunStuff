  double findMedianSortedArrays(vector<int>& nums) {
      auto max_heap = priority_queue<int>();
      auto min_heap = priority_queue<int, vector<int>, greater<int>>();

      for (auto i = 0; i < nums.size(); ++i) {
          max_heap.push(nums[i]);

          if (max_heap.size() - min_heap.size() > 1) {
              min_heap.push(max_heap.top());
              max_heap.pop();
          } else {
              if (!min_heap.empty()) {
                  auto max_heap_top = max_heap.top();
                  auto min_heap_top = min_heap.top();
                  if (max_heap_top > min_heap_top) {
                      max_heap.pop();
                      min_heap.pop();

                      max_heap.push(min_heap_top);
                      min_heap.push(max_heap_top);
                  }
              }
          }
      }
      
      auto max_heap_size = max_heap.size();
      auto min_heap_size = min_heap.size();

      if (max_heap_size == min_heap_size) {
          return (max_heap.top() + min_heap.top()) / 2.0;
      } else {
          return max_heap_size > min_heap_size
              ? max_heap.top()
              : min_heap.top();
      }
  }
