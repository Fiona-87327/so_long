/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyawang <jiyawang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 02:32:18 by jiyawang          #+#    #+#             */
/*   Updated: 2025/09/21 02:48:11 by jiyawang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
#define SO_LONG_H

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"
#include "mlx.h"

#define TILE_SIZE 32

// 地图结构体
typedef struct s_map {
    char    **grid;      // 二维地图数组（每行一个字符串）
    int     rows;        // 行数
    int     cols;        // 列数
    int     n_player;    // 玩家个数
    int     n_exit;      // 出口个数
    int     n_collect;   // 收集物个数
}   t_map;

// 游戏主数据结构
typedef struct s_game {
    void    *mlx;       // MLX 指针
    void    *win;       // 窗口指针
    t_map   *map;       // 地图指针
    int     player_x;   // 玩家当前横坐标
    int     player_y;   // 玩家当前纵坐标
    int     move_count; // 移动次数
    int     collected;  // 收集物已获得数量
    // 图片资源（可根据实际扩展）
    void    *img_wall;
    void    *img_floor;
    void    *img_player;
    void    *img_collect;
    void    *img_exit;
}   t_game;

// 解析地图
t_map   *parse_map(const char *filename);
// 释放地图内存
void    free_map_grid(char **grid, int rows);
// 初始化游戏和窗口
int     init_mlx(t_game *game);
// 主游戏循环、事件处理
int     handle_keypress(int keycode, t_game *game);
// 错误输出
void    error_exit(const char *msg);
// 其他工具函数可自行扩展

#endif
