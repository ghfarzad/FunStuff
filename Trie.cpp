#include <bitset>
#include <iostream>
#include <map>
#include <memory>
#include <stack>
#include <string>
#include <vector>

using namespace std;

struct Node
    : enable_shared_from_this<Node>
{

    using Edges = bitset<128>;
    using Children = map<char, shared_ptr<Node>>;

    Node(const string& s) : value(s) {}

    void Add(const string& s) {
        auto node = shared_from_this();
        auto unfound_char_index = 0;
        for (auto i = 0; i < s.length(); ++i) {
            if (node->edges[(int)(s[i])]) {
                node = node->children[s[i]];
            } else {
                unfound_char_index = i;
                break;
            }
        }

        for (auto i = unfound_char_index; i < s.length(); ++i) {
            auto new_node = make_shared<Node>(node->value + s[i]);

            node->edges.set((int)(s[i]));
            node->children[s[i]] = new_node;
            node = new_node;
        }
        node->is_full_entry = true;
    }

    vector<string> Find(const string& s) {
        auto ret = vector<string>();

        auto s_length = s.size();
        auto node = shared_from_this();
        auto i = 0;
        while (node->edges[(int)(s[i])] && i < s_length) {
            node = node->children[s[i]];
            ++i;
        }

        if (i < s_length) {
            return ret;
        }

        auto node_stack = stack<shared_ptr<Node>>();
        node_stack.push(node);

        auto process_node = [&](shared_ptr<Node> node) {
            if (node->IsLeaf()) {
                ret.push_back(node->value);
            } else {
                node_stack.push(node);
            }
        };

        while (!node_stack.empty()) {
            auto top = node_stack.top();
            node_stack.pop();

            if (top->is_full_entry) {
                ret.push_back(top->value);
            }

            for (auto itr = top->children.begin(); itr != top->children.end(); ++itr) {
                process_node(itr->second);
            }
        }

        return ret;
    }

    bool IsLeaf() {
        return edges.none();
    }

    void Display() {
        auto edges = GetEdgeString();
        cout << "is_leaf: "       << IsLeaf()      << '\n';
        cout << "is_full_entry: " << is_full_entry << '\n';
        cout << "value: "         << value         << '\n';
        cout << "edges: "         << edges         << '\n';
        cout << "---------------" << endl;

        for (auto i = 0; i < edges.size(); ++i) {
            children[edges[i]]->Display();
        }
    }

    string GetEdgeString() {
        auto tmp = edges.to_string();
        string edges_s;
        for (auto i = 0; i < tmp.size(); ++i)
        return edges_s;;
    }

    string   value;
    bool     is_full_entry = false;
    Edges    edges;
    Children children;
};

int main() {
    auto root = make_shared<Node>("");
    root->Add("hack");
    root->Add("hackerrank");

    auto result = root->Find("hac");
    for (auto i = 0; i < result.size(); ++i) {
        cout << result[i] << endl;
    }

    return 0;
}
