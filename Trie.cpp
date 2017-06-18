#include "Trie.h"

Node::Node()
{
	is_leaf = true;
	pattern_number = 0;
	exit_link = nullptr;
}

Trie::Trie() 
{
    root = new Node;
    pattern_amount = 0;
    pattern_length = (int*)malloc(sizeof(int));
    pattern_length[0] = 0;
}

bool Trie::InsertPattern(int pattern_number) 
{
    int pattern_size = 0;
    bool is_inserted = false;
    Node* node = root;

    std::string str,temp;
    getline(std::cin,temp);
    std::stringstream line(temp);

    while (line >> str) 
	{
        pattern_size++;
        is_inserted = true;

        for(int i = 0; i < str.size(); i++) str[i] = (char) tolower(str[i]);

        if (node->children.find(str) == node->children.end()) 
		{
            Node* new_son = new Node;
            node->children.insert(make_pair(str, new_son));
            node->is_leaf = false;
            node = new_son;
        }    
        else node = node->children.find(str)->second;
    }

    if (is_inserted) 
	{
        node->pattern_number = pattern_number;
        pattern_amount++;
        pattern_length = (int*) realloc(pattern_length, sizeof(int) * (pattern_number + 1));
        pattern_length[pattern_amount] = pattern_size;
        if (pattern_length[0] < pattern_size) pattern_length[0] =pattern_size;
    }
    return is_inserted;
}

void Trie::CreatingLink() 
{
    for(auto i : root->children) i.second->fail_link = root;
    root->fail_link = root;

    std::queue<Node*> nodes_to_visit;
    nodes_to_visit.push(root);

    while(!nodes_to_visit.empty()) 
	{
        Node* node = nodes_to_visit.front();
        if (node != root && !node->is_leaf) 
		{
            for(auto i : node->children) 
			{
				Node* w = node->fail_link;
                Node* child = i.second;
                std::string x = i.first;

                while( w->children.find(x) == w->children.end() && w != root) w = w->fail_link;

                if (w->children.find(x) != w->children.end()) child->fail_link = w->children.find(x)->second;
                else child->fail_link = root;

                if (child->fail_link->pattern_number) child->exit_link = child->fail_link;
                else child->exit_link = child->fail_link->exit_link;
            }        
        }
        nodes_to_visit.pop();
		if (!node->is_leaf)
		{
			for (auto i : node->children) nodes_to_visit.push(i.second);
		}  
    }
}

void Trie::Search() 
{
    std::string str,temp;
    std::stringstream line;
    Coordinate current_position;
    current_position.x = 1;
    current_position.y = 1;
    std::vector<Coordinate> coordinates(pattern_length[0]);

    int coord_index = 0;
	Node* father = root;
    Node* son;

    getline(std::cin,temp);
    line.str(temp);

    bool not_end = true;
    line >> str;
    for(int i = 0; i < str.size(); i++) str[i] = (char) tolower(str[i]);
    coordinates[coord_index] = current_position;
    do 
	{
        while (father->children.find(str) != father->children.end()) 
		{
            son = father->children.find(str)->second;
            Node* exit_node = son->exit_link;
            if (son->pattern_number) 
			{
                int index = coord_index - pattern_length[son->pattern_number] + 1;
                if (index < 0) index = pattern_length[0] + index;
                printf("%d, %d, %d\n",coordinates[index].y, coordinates[index].x, son->pattern_number);
            }    
            while (exit_node) 
			{
                int index = coord_index - pattern_length[exit_node->pattern_number] + 1;
                if (index < 0) index = pattern_length[0] + index;
                printf("%d, %d, %d\n",coordinates[index].y, coordinates[index].x, exit_node->pattern_number);
                exit_node = exit_node->exit_link;
            }
            father = son;
            str.clear();
            if (line >> str) 
			{
                current_position.x++;
                coord_index++;
                if (coord_index == pattern_length[0]) coord_index = 0;        
            }
            else  
			{
                current_position.x = 1;
                current_position.y++;
                coord_index++;

                if (coord_index == pattern_length[0]) coord_index = 0;

                temp.clear();

                if (!getline(std::cin, temp)) not_end = false;

                if (temp.size() < 1) 
				{
                    while(temp.size() < 1 && not_end) 
					{
                        current_position.y++;
                        if(!getline(std::cin,temp)) not_end = false;
                    }
                    line.clear();
                    line.str(temp);
                    line >> str;
                }
                else 
				{
                    line.clear();
                    line.str(temp);
                    line >> str;
                }
            }

            for(int i = 0; i < str.size(); i++) str[i] = (char) tolower(str[i]);

            coordinates[coord_index] = current_position;
        }

        if (father == root) 
		{
            if (line >> str) 
			{
                current_position.x++;
                coord_index++;
                if (coord_index == pattern_length[0]) coord_index = 0;        
            }
            else  
			{
				current_position.x = 1;
				current_position.y++;
				coord_index++;

				if (coord_index == pattern_length[0]) coord_index = 0;

				temp.clear();

				if (!getline(std::cin, temp)) not_end = false;

				if (temp.size() < 1)
				{
					while (temp.size() < 1 && not_end)
					{
						current_position.y++;
						if (!getline(std::cin, temp)) not_end = false;
					}
					line.clear();
					line.str(temp);
					line >> str;
				}
				else
				{
					line.clear();
					line.str(temp);
					line >> str;
				}
			}

			for (int i = 0; i < str.size(); i++) str[i] = (char)tolower(str[i]);

			coordinates[coord_index] = current_position;
        }
        else father = father->fail_link;
        
    }
	while (not_end);

}

void Trie::DeleteTrie(Node* node) 
{
    for (auto it : node->children) DeleteTrie(it.second);
    delete node;
}

Trie::~Trie() 
{
    DeleteTrie(root);
    root = 0;
    delete pattern_length;
}
