/*
** EPITECH PROJECT, 2021
** iron
** File description:
** goat
*/

#ifndef __LIB_IRON_GOAT_TILED_H__
    #define __LIB_IRON_GOAT_TILED_H__

    #include <erty/evector.h>
    #include <erty/opt.h>
    #include <erty/ectypes.h>
    #include <erty/json.h>
    #include <iron_goat/deser.h>

    typedef struct iron_goat_layer ig_layer_t;
    typedef struct iron_goat_map ig_map_t;
    typedef struct iron_goat_chunk ig_chunk_t;
    typedef struct iron_goat_point ig_point_t;
    typedef struct iron_goat_text ig_text_t;
    typedef struct iron_goat_object ig_object_t;
    typedef struct iron_goat_property ig_prop_t;
    typedef struct iron_goat_tileoffset ig_tileoffset_t;
    typedef struct iron_goat_frame ig_frame_t;
    typedef struct iron_goat_grid ig_grid_t;
    typedef struct iron_goat_terrain ig_terrain_t;
    typedef struct iron_goat_tile_terrain ig_tile_terrain_t;
    typedef struct iron_goat_tile ig_tile_t;
    typedef struct iron_goat_wangcolor ig_wangcolor_t;
    typedef struct iron_goat_wangtile ig_wangtile_t;
    typedef struct iron_goat_wangset ig_wangset_t;
    typedef struct iron_goat_tileset ig_goat_tileset_t;

    void destroy_iron_goat_wangset(struct iron_goat_wangset *self);
    void destroy_iron_goat_chunk(struct iron_goat_chunk *self);
    void destroy_iron_goat_layer(struct iron_goat_layer *self);
    void destroy_iron_goat_map(struct iron_goat_map *self);
    void destroy_iron_goat_object(struct iron_goat_object *self);
    void destroy_iron_goat_property(struct iron_goat_property *self);
    void destroy_iron_goat_terrain(struct iron_goat_terrain *self);
    void destroy_iron_goat_text(struct iron_goat_text *self);
    void destroy_iron_goat_tile(struct iron_goat_tile *self);
    void destroy_iron_goat_tileset(struct iron_goat_tileset *self);
    void destroy_iron_goat_wangcolor(struct iron_goat_wangcolor *self);
    void destroy_iron_goat_wangset(struct iron_goat_wangset *self);

    typedef enum {
        MAP_ORTHOGONAL,
        MAP_ISOMETRIC,
        MAP_STAGGERED,
        MAP_HEXAGONAL
    } ig_map_orient_t;

    typedef enum {
        MAP_RIGHT_DOWN,
        MAP_RIGHT_UP,
        MAP_LEFT_DOWN,
        MAP_LEFT_UP
    } ig_map_renderorder_t;

    typedef enum {
        MAP_STAG_X,
        MAP_STAG_Y
    } ig_map_staggeraxis_t;

    typedef enum {
        MAP_STAG_ODD,
        MAP_STAG_EVEN
    } ig_map_staggerindex_t;

    typedef enum {
        LAYER_ZLIB,
        LAYER_GZIP,
        LAYER_NONE
    } ig_layer_compression_t;

    typedef enum {
        LAYER_TOPDOWN,
        LAYER_INDEX
    } ig_layer_draworder_t;

    typedef enum {
        LAYER_TILELAYER,
        LAYER_OBJECTGROUP,
        LAYER_IMAGELAYER,
        LAYER_GROUP
    } ig_layer_type_t;

    typedef enum {
        LAYER_CSV,
        BASE64
    } ig_layer_encoding_t;

    typedef enum {
        HALIGN_CENTER,
        HALIGN_RIGHT,
        HALIGN_JUSTIFY,
        HALIGN_LEFT
    } ig_text_halign_t;

    typedef enum {
        VALIGN_CENTER,
        VALIGN_BOTTOM,
        VALIGN_TOP
    } ig_text_valign_t;

    typedef enum {
        OBJECT_ELLIPSE,
        OBJECT_POINT,
        OBJECT_RECT,
        OBJECT_POLYGON,
        OBJECT_POLYLINE,
        OBJECT_TEXT,
        OBJECT_TILE
    } ig_object_type_t;

    typedef enum {
        PROP_STRING,
        PROP_INT,
        PROP_FLOAT,
        PROP_BOOL,
        PROP_COLOR,
        PROP_FILE
    } ig_property_type_t;

    typedef enum {
        GRID_ORTHOGONAL,
        GRID_ISOMETRIC
    } ig_grid_orientation_t;

    union iron_goat_property_value {
        char *str;
        i64_t i;
        f64_t f;
        bool b;
        u32_t color;
        char *file;
    };

    struct iron_goat_grid {
        u64_t height;
        ig_grid_orientation_t orientation;
        u64_t width;
    };

    struct iron_goat_tileoffset {
        i64_t x;
        i64_t y;
    };

    struct iron_goat_frame {
        u64_t duration;
        u64_t tileid;
    };

    struct iron_goat_terrain {
        char *name;
        VECTOR(ig_prop) *props;
        u64_t tile;
    };

    struct iron_goat_tile_terrain {
        size_t tile[4];
    };

    struct iron_goat_wangcolor {
        u32_t color;
        char *name;
        f64_t probability;
        u64_t tile;
    };

    struct iron_goat_wangtile {
        bool dflip;
        bool hflip;
        u64_t tileid;
        bool vflip;
        u8_t wangid;
    };

    struct iron_goat_wangset {
        VECTOR(ig_wangcolor) *cornercolors;
        VECTOR(ig_wangcolor) *edgecolors;
        char *name;
        VECTOR(ig_prop) *properties;
        u64_t tile;
        VECTOR(ig_wangtile) *wangtiles;
    };

    struct iron_goat_tileset {
        u32_t backgroundcolor;
        u64_t columns;
        u64_t firstgid;
        ig_grid_t grid;
        char *image;
        u64_t imageheight;
        u64_t imagewidth;
        u64_t margin;
        char *name;
        VECTOR(ig_prop) *properties;
        char *source;
        u64_t spacing;
        VECTOR(ig_terrain) *terrains;
        u64_t tilecount;
        char *tiledversion;
        u64_t tileheight;
        ig_tileoffset_t tileoffset;
        VECTOR(ig_tile) *tiles;
        u64_t tilewidth;
        OPT(u32) transparentcolor;
        VECTOR(ig_wangset) *wangsets;
    };

    struct iron_goat_property {
        char *name;
        ig_property_type_t type;
        union iron_goat_property_value value;
    };

    struct iron_goat_object {
        ig_object_type_t kind;
        f64_t height;
        u64_t id;
        char *name;
        VECTOR(ig_prop) *properties;
        f64_t rotation;
        char *template;
        char *type;
        bool visible;
        f64_t width;
        f64_t x;
        f64_t y;
        u64_t gid;
        VECTOR(ig_point) *polygon;
        VECTOR(ig_text) *text;
    };

    struct iron_goat_text {
        bool bold;
        u32_t color;
        char *fontfamily;
        ig_text_halign_t halign;
        bool italic;
        bool kerning;
        u64_t pixelsize;
        bool strikeout;
        char *text;
        bool underline;
        ig_text_valign_t valign;
        bool wrap;
    };

    struct iron_goat_point {
        f64_t x;
        f64_t y;
    };

    struct iron_goat_chunk {
        VECTOR(ig_u64) *data;
        u64_t height;
        u64_t width;
        i64_t x;
        i64_t y;
    };

    INIT_VECTOR(ig_obj, struct iron_goat_object, destroy_iron_goat_object);

    struct iron_goat_layer {
        u64_t id;
        char *name;
        i64_t x;
        i64_t y;
        u64_t width;
        u64_t height;
        i64_t startx;
        i64_t starty;
        f64_t offsetx;
        f64_t offsety;
        f64_t opacity;
        bool visible;
        ig_layer_type_t type;
        VECTOR(ig_chunk) *chunks;
        ig_layer_compression_t compression;
        VECTOR(ig_u64) *data;
        ig_layer_encoding_t encoding;
        ig_layer_draworder_t draworder;
        VECTOR(ig_obj) objects;
        u32_t transparentcolor;
        char *image;
        VECTOR(ig_layer) *layers;
        VECTOR(ig_prop) *properties;
    };

    INIT_VECTOR(ig_layer, struct iron_goat_layer, destroy_iron_goat_layer);
    INIT_VECTOR(ig_tile_terrain, struct iron_goat_tile_terrain, NULL);

    struct iron_goat_tile {
        VECTOR(ig_frame) *animation;
        u64_t id;
        char *image;
        u64_t imageheight;
        u64_t imagewidth;
        OPT(ig_layer) objectgroup;
        f64_t probability;
        VECTOR(ig_prop) *properties;
        OPT(ig_tile_terrain) terrain;
        char *type;
    };

    struct iron_goat_map {
        u32_t backgroundcolor;
        u64_t height;
        i64_t hexsidelenght;
        bool infinite;
        VECTOR(ig_layer) *layers;
        i64_t nextlayerid;
        i64_t nextobjectid;
        ig_map_orient_t orientation;
        VECTOR(ig_prop) *properties;
        ig_map_renderorder_t renderorder;
        ig_map_staggeraxis_t staggeraxis;
        ig_map_staggerindex_t staggerindex;
        char *tiledversion;
        u64_t tileheight;
        VECTOR(ig_tile) *tilesets;
        u64_t tilewidth;
        u64_t width;
    };

    INIT_VECTOR(ig_u64, u64_t, NULL);
    INIT_VECTOR(ig_i64, i64_t, NULL);

    INIT_VECTOR(ig_map, struct iron_goat_map, destroy_iron_goat_map);
    INIT_VECTOR(ig_chunk, struct iron_goat_chunk, destroy_iron_goat_chunk);
    INIT_VECTOR(ig_point, struct iron_goat_point, NULL);
    INIT_VECTOR(ig_text, struct iron_goat_text, destroy_iron_goat_text);
    INIT_VECTOR(ig_prop, struct iron_goat_property, destroy_iron_goat_property);
    INIT_VECTOR(ig_tileoffset, struct iron_goat_tileoffset, NULL);
    INIT_VECTOR(ig_frame, struct iron_goat_frame, NULL);
    INIT_VECTOR(iron_goat_grid, struct iron_goat_grid, NULL);
    INIT_VECTOR(ig_terrain, struct iron_goat_terrain,
                            destroy_iron_goat_terrain);
    INIT_VECTOR(ig_tile, struct iron_goat_tile, destroy_iron_goat_tile);
    INIT_VECTOR(ig_wangcolor, struct iron_goat_wangcolor,
                                destroy_iron_goat_wangcolor);
    INIT_VECTOR(ig_wangtile, struct iron_goat_wangtile, NULL);
    INIT_VECTOR(ig_wangset, struct iron_goat_wangset,
                            destroy_iron_goat_wangset);
    INIT_VECTOR(ig_tileset, struct iron_goat_tileset,
                            destroy_iron_goat_tileset);

#endif