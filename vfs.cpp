#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

class VirtualFileSystem
{
private:
    struct Node
    {
        std::string name;
        bool isDirectory;
        std::string content;
        std::unordered_map<std::string, Node *> children;

        Node(const std::string &n, bool isDir) : name(n), isDirectory(isDir) {}
    };

    Node *root;
    Node *currentDirectory;

    std::vector<std::string> splitPath(const std::string &path)
    {
        std::vector<std::string> parts;
        std::stringstream ss(path);
        std::string part;
        while (std::getline(ss, part, '/'))
        {
            if (!part.empty())
            {
                parts.push_back(part);
            }
        }
        return parts;
    }

    Node *navigateTo(const std::string &path)
    {
        std::vector<std::string> parts = splitPath(path);
        Node *current = (path[0] == '/') ? root : currentDirectory;

        for (const auto &part : parts)
        {
            if (part == "..")
            {
                if (current != root)
                {
                    current = findParent(current);
                }
            }
            else if (current->children.find(part) != current->children.end())
            {
                current = current->children[part];
            }
            else
            {
                return nullptr;
            }
        }
        return current;
    }

    Node *findParent(Node *node)
    {
        for (Node *current = root; current != nullptr; current = current->children.begin()->second)
        {
            for (const auto &child : current->children)
            {
                if (child.second == node)
                {
                    return current;
                }
            }
        }
        return root;
    }

public:
    VirtualFileSystem()
    {
        root = new Node("/", true);
        currentDirectory = root;
    }

    void mkdir(const std::string &path)
    {
        std::vector<std::string> parts = splitPath(path);
        Node *current = currentDirectory;

        for (const auto &part : parts)
        {
            if (current->children.find(part) == current->children.end())
            {
                current->children[part] = new Node(part, true);
            }
            current = current->children[part];
        }
    }

    void cd(const std::string &path)
    {
        Node *target = navigateTo(path);
        if (target && target->isDirectory)
        {
            currentDirectory = target;
        }
        else
        {
            std::cout << "Directory not found: " << path << std::endl;
        }
    }

    void ls(const std::string &path = "")
    {
        Node *target = path.empty() ? currentDirectory : navigateTo(path);
        if (target && target->isDirectory)
        {
            for (const auto &child : target->children)
            {
                std::cout << child.first << (child.second->isDirectory ? "/" : "") << std::endl;
            }
        }
        else
        {
            std::cout << "Directory not found: " << path << std::endl;
        }
    }

    void touch(const std::string &filename)
    {
        if (currentDirectory->children.find(filename) == currentDirectory->children.end())
        {
            currentDirectory->children[filename] = new Node(filename, false);
        }
    }

    void writeFile(const std::string &filename, const std::string &content)
    {
        if (currentDirectory->children.find(filename) != currentDirectory->children.end() &&
            !currentDirectory->children[filename]->isDirectory)
        {
            currentDirectory->children[filename]->content = content;
        }
        else
        {
            std::cout << "File not found: " << filename << std::endl;
        }
    }

    void cat(const std::string &filename)
    {
        if (currentDirectory->children.find(filename) != currentDirectory->children.end() &&
            !currentDirectory->children[filename]->isDirectory)
        {
            std::cout << currentDirectory->children[filename]->content << std::endl;
        }
        else
        {
            std::cout << "File not found: " << filename << std::endl;
        }
    }

    void rm(const std::string &path)
    {
        Node *parent = currentDirectory;
        std::string name = path;
        size_t pos = path.find_last_of('/');
        if (pos != std::string::npos)
        {
            parent = navigateTo(path.substr(0, pos));
            name = path.substr(pos + 1);
        }

        if (parent && parent->children.find(name) != parent->children.end())
        {
            delete parent->children[name];
            parent->children.erase(name);
        }
        else
        {
            std::cout << "File or directory not found: " << path << std::endl;
        }
    }
};

int main()
{
    VirtualFileSystem vfs;
    std::string command, arg1, arg2;

    while (true)
    {
        std::cout << "> ";
        std::cin >> command;

        if (command == "exit")
        {
            break;
        }
        else if (command == "mkdir")
        {
            std::cin >> arg1;
            vfs.mkdir(arg1);
        }
        else if (command == "cd")
        {
            std::cin >> arg1;
            vfs.cd(arg1);
        }
        else if (command == "ls")
        {
            std::getline(std::cin, arg1);
            arg1.erase(0, arg1.find_first_not_of(" \t")); // Trim leading whitespace
            if (!arg1.empty() && arg1.back() == '/')
            {
                arg1.pop_back(); // Remove trailing slash
            }
            vfs.ls(arg1);
        }
        else if (command == "touch")
        {
            std::cin >> arg1;
            vfs.touch(arg1);
        }
        else if (command == "write")
        {
            std::cin >> arg1;
            std::getline(std::cin >> std::ws, arg2);
            vfs.writeFile(arg1, arg2);
        }
        else if (command == "cat")
        {
            std::cin >> arg1;
            vfs.cat(arg1);
        }
        else if (command == "rm")
        {
            std::cin >> arg1;
            vfs.rm(arg1);
        }
        else
        {
            std::cout << "Unknown command: " << command << std::endl;
        }
    }

    return 0;
}