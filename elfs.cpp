#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <filesystem>

#define ELFS_MAGIC 0x454C4653
#define BLOCK_SIZE 4096
#define MAX_FILENAME 32

typedef struct {
    uint32_t magic;
    uint64_t block_count;
    uint32_t root_inode_idx;
} elfs_superblock_t;

typedef struct {
    char name[MAX_FILENAME];
    uint32_t inode_id;
    bool is_directory;
} elfs_dirent_t;

class ELFS {
public:
    std::string disk_path;
    ELFS(std::string path) : disk_path(path) {}

    void format_disk() {
        std::ofstream disk(disk_path, std::ios::binary | std::ios::out);
        if (!disk) return;

        elfs_superblock_t sb = {ELFS_MAGIC, 1000000, 0};
        disk.write(reinterpret_cast<char*>(&sb), sizeof(sb));

        elfs_dirent_t root_dirs[3];
        strncpy(root_dirs[0].name, "sys", MAX_FILENAME); root_dirs[0].inode_id = 1; root_dirs[0].is_directory = true;
        strncpy(root_dirs[1].name, "bin", MAX_FILENAME); root_dirs[1].inode_id = 2; root_dirs[1].is_directory = true;
        strncpy(root_dirs[2].name, "usr", MAX_FILENAME); root_dirs[2].inode_id = 3; root_dirs[2].is_directory = true;

        disk.write(reinterpret_cast<char*>(root_dirs), sizeof(root_dirs));
        disk.seekp(1ULL << 40); // Sparse seek
        disk.put(0);
        disk.close();
        std::cout << "[ELFS] Disk formatted with /sys, /bin, /usr." << std::endl;
    }

    void add_file(std::string filename) {
        std::string ext = std::filesystem::path(filename).extension().string();
        std::string target = (ext == ".sys" || ext == ".init") ? "/sys" : 
                            (ext == ".img" || ext == ".iso") ? "/bin" : "/usr";
        std::cout << "[ROUTING] " << filename << " -> " << target << std::endl;
    }
};

int main(int argc, char* argv[]) {
    ELFS my_fs("elfs_disk.img");
    if (argc < 2) return 1;
    std::string cmd = argv[1];
    if (cmd == "format") my_fs.format_disk();
    else if (cmd == "add" && argc == 3) my_fs.add_file(argv[2]);
    return 0;
}
