#pragma once

#include <environment/position.hpp>
#include <environment/graph_guidance.hpp>
#include <environment/map.hpp>

#include <array>
#include <cstdint>
#include <vector>

#include <settings.hpp>

// Contains information about graph.
// About edges, transform position to node and back.
// Undirected edges.
// 0 = NONE
class Graph {

#ifdef ENABLE_ROTATE_MODEL
    // pos_to_node[pos][dir] = graph node
    std::vector<std::array<uint32_t, DIRECTIONS_NUM>> pos_to_node;
#else
    // pos_to_node[pos] = graph node
    std::vector<uint32_t> pos_to_node;
#endif

    // node_to_pos[node] = position
    std::vector<Position> node_to_pos;

    // to_node[node][action] = to node
    std::vector<std::array<uint32_t, ACTIONS_NUM>> to_node;

    // to_edge[node][action] = to edge
    std::vector<std::array<uint32_t, ACTIONS_NUM>> to_edge;

    // to_weight[node][action] = weight
    std::vector<std::array<uint32_t, ACTIONS_NUM>> weight;

    uint32_t edges_size = 0;

public:
    Graph() = default;

    explicit Graph(const Map &map, const GraphGuidance &gg);

    [[nodiscard]] uint32_t get_nodes_size() const;

    [[nodiscard]] uint32_t get_edges_size() const;

    // graph node -> Position
    [[nodiscard]] Position get_pos(uint32_t node) const;

    // Position -> graph node
    [[nodiscard]] uint32_t get_node(const Position &pos) const;

    // (pos, dir) -> graph node
    [[nodiscard]] uint32_t get_node(uint32_t pos
#ifdef ENABLE_ROTATE_MODEL
            , uint32_t dir
#endif
    ) const;

    // graph node + action -> graph node
    [[nodiscard]] uint32_t get_to_node(uint32_t node, uint32_t action) const;

    // graph node + action -> graph edge
    [[nodiscard]] uint32_t get_to_edge(uint32_t node, uint32_t action) const;

    // graph node + action -> edge weight from GraphGuidance
    [[nodiscard]] uint32_t get_weight(uint32_t node, uint32_t action) const;
};

Graph &get_graph();
