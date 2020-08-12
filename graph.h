#pragma once

#include <cmath>
#include <unordered_map>
#include <vector>
#include <set>

#include "test_runner.h"
#include "date.h"

struct Transmission{
public:
    Transmission() = default;

    Transmission(int train_id, int id_d, int id_a, float price, Date t_d, Date t_a)
    : id(train_id)
    , id_departure(id_d)
    , id_arrival(id_a)
    , price(price)
    , t_departure(t_d)
    , t_arrival(t_a)
    {
        if (t_departure > t_arrival){
            t_arrival.set_d(1);
        }
    }

    Date t_departure, t_arrival;
    float price;
    int id, id_departure, id_arrival;
};

std::istream& operator>>(std::istream& stream, Transmission& tr);
std::ostream& operator<<(std::ostream& stream, const Transmission& tr);
std::ostream& operator<<(std::ostream& stream, const std::vector<Transmission>& trs);


class Graph{
    using id_t = int;

    struct Result{
        size_t idx;
        float price;
        Date date;
        int n;
    };

public:
    void insert(id_t id, Transmission tr);
    std::vector<std::vector<id_t>> search(id_t id_begin, id_t id_final, bool flag);

private:
    std::unordered_map<id_t, std::set<id_t>> neighbours;
    std::unordered_map<id_t, Transmission> transmissions;
    std::vector<std::vector<id_t>> results;
    //minimum acceptable timedelta between trains, s
    int delta = 900;

    id_t dfs(id_t id, id_t id_goal, std::vector<id_t> path);
};
