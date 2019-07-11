template <class Node, class Data, class Hash = HASH_NAMESPACE::hash<const char *>>
class HashRing
{
public:
    typedef std::map<size_t, Node> NodeMap;

    HashRing(unsigned int replicas)
        : replicas_(replicas), hash_(HASH_NAMESPACE::hash<const char *>())
    {
    }

    HashRing(unsigned int replicas, const Hash &hash)
        : replicas_(replicas), hash_(hash)
    {
    }

    size_t AddNode(const Node &node);
    void RemoveNode(const Node &node);
    const Node &GetNode(const Data &data) const;

private:
    NodeMap ring_;
    const unsigned int replicas_;
    Hash hash_;
};

template <class Node, class Data, class Hash>
size_t HashRing<Node, Data, Hash>::AddNode(const Node &node)
{
    size_t hash;
    std::string nodestr = Stringify(node);
    for (unsigned int r = 0; r < replicas_; r++)
    {
        hash = hash_((nodestr + Stringify(r)).c_str());
        ring_[hash] = node;
    }
    return hash;
}

template <class Node, class Data, class Hash>
void HashRing<Node, Data, Hash>::RemoveNode(const Node &node)
{
    std::string nodestr = Stringify(node);
    for (unsigned int r = 0; r < replicas_; r++)
    {
        size_t hash = hash_((nodestr + Stringify(r)).c_str());
        ring_.erase(hash);
    }
}

template <class Node, class Data, class Hash>
const Node &HashRing<Node, Data, Hash>::GetNode(const Data &data) const
{
    if (ring_.empty())
    {
        throw EmptyRingException();
    }
    size_t hash = hash_(Stringify(data).c_str());
    typename NodeMap::const_iterator it;
    // Look for the first node >= hash
    it = ring_.lower_bound(hash);
    if (it == ring_.end())
    {
        // Wrapped around; get the first node
        it = ring_.begin();
    }
    return it->second;
}