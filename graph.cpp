#include "graph.h"

std::istream& operator>>(std::istream& stream, Transmission& tr){
    int id, depID, arrID;
    float price;
    Date depT, arrT;
    stream >> id;
    if (stream.peek() == ',') stream.ignore();
    stream >> depID;
    if (stream.peek() == ',') stream.ignore();
    stream >> arrID;
    if (stream.peek() == ',') stream.ignore();
    stream >> price;
    if (stream.peek() == ',') stream.ignore();
    stream >> depT;
    if (stream.peek() == ',') stream.ignore();
    stream >> arrT;
    tr = Transmission{id, depID, arrID, price, depT, arrT};
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Transmission& tr){
    stream << "     Train #" << tr.id << " from " << tr.id_departure << " to "
           << tr.id_arrival << std::endl
           << tr.t_departure << " - " << tr.t_arrival << ", " << tr.price << "$`";
    return stream;
}


std::ostream& operator<<(std::ostream& stream, const std::vector<Transmission>& trs){
    for (int i = 0; i + 1 < trs.size(); ++i){
        stream << trs[i] << std::endl;
        stream << "Wait for " << trs[i + 1].t_departure - trs[i].t_arrival << std::endl;
    }
    stream << trs.back();
    return stream;
}

void Graph::insert(id_t id, Transmission tr){
    transmissions[id] = tr;
    neighbours[tr.id_departure].insert(id);
}

std::vector<std::vector<int>> Graph::search(id_t id_begin, id_t id_final, bool flag){
    results.clear();
    if (!neighbours.contains(id_begin))
        return {};
    for (auto id : neighbours[id_begin]) {
        std::vector<id_t> path {id, };
        dfs(id, id_final, path);
    }
    Date time;
    float price = 0.0;
    size_t i = 0;
    std::vector<Result> resultSqueezed;
    for (const auto& r : results){
        Date t; float p = 0.0; int n = 0;
        for (id_t id : r){
            Transmission tr = transmissions[id];
            p += tr.price;
            ++n;
        }
        t = transmissions[r.back()].t_arrival - transmissions[r.front()].t_departure;
        resultSqueezed.push_back(Result{i++, p, t, n});
        price = max(price, p);
        time = max(time, t);
    }
    std::sort(resultSqueezed.begin(), resultSqueezed.end(),
              [time, price](const Result& lhs, const Result& rhs) {
                  return log(lhs.n * (lhs.date.get() * lhs.price)/(time.get() * price)) <
                         log(rhs.n * (rhs.date.get() * rhs.price)/(time.get() * price));
              } );
    std::vector<std::vector<id_t>> resultFinal;
    int j = 0;
    for (const auto& r : resultSqueezed){
        resultFinal.push_back(results[r.idx]);
        if(!flag) continue;
        std::cout << "#" << ++j;
        for (int i =0; i + 1 < results[r.idx].size(); ++i) {
             std::cout << transmissions[results[r.idx][i]] << std::endl;
            std::cout << "Wait for " << transmissions[results[r.idx][i + 1]].t_departure -
                                        transmissions[results[r.idx][i]].t_arrival << std::endl;
        }
        std::cout << transmissions[results[r.idx].back()] << std::endl;
        std::cout << "<<";
        for (int i = 0; i < 35; ++i)
            std::cout << "-";
        std::cout << ">>" << std::endl;
        std::cout << "Total: " << r.price << "$`, " << r.date.print() << std::endl << std::endl << std::endl;
    }
    return resultFinal;
}

int Graph::dfs(id_t id, id_t id_goal, std::vector<id_t> path){
    if (transmissions.at(id).id_arrival == id_goal){
        results.push_back(path);
        return id;
    }
    for (auto id_next : neighbours.at(transmissions.at(id).id_arrival)) {
        if (transmissions.at(id).t_arrival < transmissions.at(id_next).t_departure && // we need to arrive before
            (transmissions.at(id_next).t_departure - transmissions.at(id).t_arrival ) >= Date{delta}) { // at least {delta} min between trains
            std::vector<id_t> path2{path};
            path2.push_back(id_next);
            dfs(id_next, id_goal, path2);
        }
    }
    return id;
}
