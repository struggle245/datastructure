#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<queue>
#include<memory>

class TrieTree
{
public:
    TrieTree()
    {
        root_=new TrieNode('\0',0);
    }
    ~TrieTree()
    {
        std::queue<TrieNode*>que;
        que.push(root_);
        while(!que.empty())
        {
            TrieNode* front=que.front();
            que.pop();
            for(auto pair:front->nodeMap_)
            {
                que.push(pair.second);
            }
            delete front;
        }
    }
    void add(const std::string& word)
    {
        TrieNode* cur=root_;
        for(int i=0;i<word.size();i++)
        {
            auto childIt=cur->nodeMap_.find(word[i]);
            if(childIt==cur->nodeMap_.end())
            {
                //创建相应字符
                TrieNode* child=new TrieNode(word[i],0);
                cur->nodeMap_.emplace(word[i],child);
                cur=child;
            }else{
                cur=childIt->second;
            }
            
        }
        cur->freq_++;
    }
    void remove(const std::string& word)
    {
        TrieNode* cur=root_;
        TrieNode* del=root_;
        char delch=word[0];
        for(int i=0;i<word.size();i++)
        {
            auto childIt=cur->nodeMap_.find(word[i]);
            if(childIt==cur->nodeMap_.end())
            {
                return;
            }
            if(cur->freq_>0||cur->nodeMap_.size()>0)
            {
                del=cur;
                delch=word[i];
            }
            cur=childIt->second;
        }
        if(cur->nodeMap_.empty())
        {
            TrieNode* child=del->nodeMap_[delch];
            del->nodeMap_.erase(delch);

            std::queue<TrieNode*>que;
            que.push(child);

            while(!que.empty())
            {
                TrieNode* front=que.front();
                que.pop();
                for(auto& pair:front->nodeMap_)
                {
                    que.push(pair.second);
                }
                delete front;
            }
        }
        else
        {
            //当前单词字符后面还有节点
            cur->freq_=0;
        }
    }
    int query(const std::string& word)
    {
        TrieNode* cur=root_;
        for(int i=0;i<word.size();i++)
        {
            auto childIt=cur->nodeMap_.find(word[i]);
            if(childIt==cur->nodeMap_.end())
            {
                return 0;
            }
            cur=childIt->second;

        }
        return cur->freq_;

    }
    void preOrder()
    {
        std::string word;
        std::vector<std::string> wordList;
        preOrder(root_,word,wordList);
        for(auto word:wordList)
        {
            std::cout<<word<<std::endl;
        }

    }
  std::vector<std::string> queryPrefix(const std::string& prefix)
    {
        TrieNode* cur=root_;
        for(int i=0;i<prefix.size();i++)
        {
            auto childIt=cur->nodeMap_.find(prefix[i]);
            if(childIt==cur->nodeMap_.end())
            {
                return {};
            }
            cur=childIt->second;
        }
        std::vector<std::string> wordlist;
        preOrder(cur,prefix,wordlist);
        return wordlist;
    }
private:
    struct TrieNode
    {
        TrieNode(char ch,int freq):ch_(ch),freq_(freq){}
        char ch_;
        int freq_;
        std::map<char,TrieNode*> nodeMap_;
    };
    TrieNode* root_; 
    void preOrder(TrieNode* cur,std::string word,std::vector<std::string>& wordList)
    {
        if(cur!=root_)
        {
            word.push_back(cur->ch_);
            if(cur->freq_>0)
            {
                wordList.push_back(word);
            }
        }
        for(auto pair:cur->nodeMap_)
        {
            preOrder(pair.second,word,wordList);
        }
    }
   
};

int main()
{
    TrieTree trie;
    trie.add("hello");
    trie.add("hello");
    trie.add("hel");
    trie.add("he");
    trie.add("heword");
    trie.add("hewsdsd");
    trie.add("hew");
    //std::cout<<trie.query("hello")<<std::endl;
    std::cout<<"=========="<<std::endl;
    trie.preOrder();
      std::cout<<"=========="<<std::endl;
    std::vector<std::string> res=trie.queryPrefix("hew");
    for(int i=0;i<res.size();i++)
    {
        std::cout<<res[i]<<std::endl;
    }
    return 0;
}