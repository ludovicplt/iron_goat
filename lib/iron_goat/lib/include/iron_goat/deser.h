/*
** EPITECH PROJECT, 2021
** deser
** File description:
** deser
*/

#ifndef __LIB_IRON_GOAT_DESER_H__
    #define __LIB_IRON_GOAT_DESER_H__

    #include <iron_goat/tiled.h>

    struct inter_fun {
        bool (*callback)();
        bool woff;
    };

    struct json_deser_data {
        char *data;
        const usize_t size_data;
        const usize_t offset;
        struct inter_fun intern;
        const int type;
    };

    struct json_deser {
        const struct json_deser_data *data;
        const usize_t size;
    };

    #define JSON_DESER(data) \
        (struct json_deser){data, ARRAY_SIZE(data)}

    bool iron_goat_deser(struct json *conf,
        struct json_deser *deser, void *data);

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

    bool iron_goat_get_string(struct json *conf, size_t offset, void *data);

    bool init_iron_goat_grid(struct json *conf, struct iron_goat_grid *self);
    bool init_iron_goat_tileoffset(struct json *conf,
                                struct iron_goat_tileoffset *self);
    bool init_iron_goat_frame(struct json *conf, struct iron_goat_frame *self);
    bool init_iron_goat_tile_terrain(struct json *conf,
                                struct iron_goat_tile_terrain *self);

    bool init_iron_goat_chunk(struct json *conf, struct iron_goat_chunk *new);

    #define DESER_CALL_INTERN(conf, new, info, tmp, ptr) \
        ((info[i].intern.woff == false) ? \
            info[i].intern.callback(conf, new) : \
            info[i].intern.callback(conf, info[i].offset, new))

    #define DESER_LOOP_INTERN_COPY(conf, new, info, tmp, ptr) \
        if (info[i].intern.callback != NULL) { \
            if (DESER_CALL_INTERN(conf, new, info, tmp, ptr) == false) \
                return (false); \
        } else { \
            ememcpy(ptr + info[i].offset, \
                    &tmp.value.v.null, info[i].size_data); \
        }

    #define DESER_LOOP(conf, new, info) \
        for (size_t i = 0; i < ARRAY_SIZE(info); i++) { \
            OPT(json) tmp = {0}; \
            char *ptr = (char *)new; \
            if ((tmp = json_get(conf, info[i].data, \
                info[i].type)).is_ok == false) \
                return (false); \
            DESER_LOOP_INTERN_COPY(conf, new, info, tmp, ptr); \
        } \
        return (true)

#endif