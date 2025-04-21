#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>
#include <vector>
#include <utility>

std::pair<std::vector<std::string>, std::vector<int>> loadData(const std::string& filename);

#endif
