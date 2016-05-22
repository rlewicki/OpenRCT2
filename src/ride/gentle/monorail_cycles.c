#pragma region Copyright (c) 2014-2016 OpenRCT2 Developers
/*****************************************************************************
 * OpenRCT2, an open source clone of Roller Coaster Tycoon 2.
 *
 * OpenRCT2 is the work of many authors, a full list can be found in contributors.md
 * For more information, visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * A full copy of the GNU General Public License can be found in licence.txt
 *****************************************************************************/
#pragma endregion

#include "../../common.h"
#include "../track_paint.h"
#include "../track.h"
#include "../vehicle_paint.h"
#include "../../interface/viewport.h"
#include "../../paint/paint.h"
#include "../../paint/supports.h"
#include "../../world/map.h"

enum
{
	SPR_MONORAIL_CYCLES_FLAT_SW_NE = 16820,
	SPR_MONORAIL_CYCLES_FLAT_NW_SE = 16821,

	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_0 = 16842,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_1 = 16843,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_2 = 16844,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_0 = 16845,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_1 = 16846,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_2 = 16847,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_0 = 16848,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_1 = 16849,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_2 = 16850,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_0 = 16851,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_1 = 16852,
	SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_2 = 16853,
};

static const uint32 monorail_cycles_track_pieces_flat[4] = {
	SPR_MONORAIL_CYCLES_FLAT_SW_NE,
	SPR_MONORAIL_CYCLES_FLAT_NW_SE
};

static const uint32 monorail_cycles_track_pieces_flat_quarter_turn_3_tiles[4][3] = {
	{
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_0,
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_1,
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SW_SE_PART_2
	},
	{
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_0,
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_1,
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NW_SW_PART_2
	},
	{
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_0,
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_1,
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_NE_NW_PART_2
	},
	{
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_0,
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_1,
		SPR_MONORAIL_CYCLES_FLAT_QUARTER_TURN_3_TILES_SE_NE_PART_2
	}
};

static paint_struct * paint_monorail_cycles_util_7c(
	bool flip,
	uint32 image_id,
	sint8 x_offset, sint8 y_offset,
	sint16 bound_box_length_x, sint16 bound_box_length_y, sint8 bound_box_length_z,
	sint16 z_offset,
	sint16 bound_box_offset_x, sint16 bound_box_offset_y, sint16 bound_box_offset_z,
	uint32 rotation
)
{
	if (flip) {
		return sub_98197C(image_id, y_offset, x_offset, bound_box_length_y, bound_box_length_x, bound_box_length_z, z_offset, bound_box_offset_y, bound_box_offset_x, bound_box_offset_z, rotation);
	}

	return sub_98197C(image_id, x_offset, y_offset, bound_box_length_x, bound_box_length_y, bound_box_length_z, z_offset, bound_box_offset_x, bound_box_offset_y, bound_box_offset_z, rotation);
}

/** rct2: 0x0088AD48 */
static void paint_monorail_cycles_track_flat(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	uint32 imageId = monorail_cycles_track_pieces_flat[(direction & 1)] | RCT2_GLOBAL(0x00F44198, uint32);
	paint_monorail_cycles_util_7c((bool) (direction & 1), imageId, 0, 0, 32, 20, 3, height, 0, 6, height, get_current_rotation());

	if (direction & 1) {
		paint_util_push_tunnel_right(height, TUNNEL_0);
	} else {
		paint_util_push_tunnel_left(height, TUNNEL_0);
	}

	metal_a_supports_paint_setup((direction & 1) ? 5 : 4, 4, -1, height, RCT2_GLOBAL(0x00F4419C, uint32));

	paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_CC, direction), 0xFFFF, 0);
	paint_util_set_general_support_height(height + 32, 0x20);
}

/** rct2: 0x*/
static void paint_monorail_cycles_station(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
}

/** rct2: 0x0088AD88 */
static void paint_monorail_cycles_track_left_quarter_turn_3_tiles(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	track_paint_util_left_quarter_turn_3_tiles_paint(3, height, direction, trackSequence, RCT2_GLOBAL(0x00F44198, uint32), monorail_cycles_track_pieces_flat_quarter_turn_3_tiles, get_current_rotation());
	track_paint_util_left_quarter_turn_3_tiles_tunnel(height, direction, trackSequence);

	switch (trackSequence) {
		case 0:
			metal_a_supports_paint_setup(4, 4, -1, height, RCT2_GLOBAL(0x00F4419C, uint32));
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_D0 | SEGMENT_C4 | SEGMENT_CC | SEGMENT_B4, direction), 0xFFFF, 0);
			break;
		case 2:
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C8 | SEGMENT_C4 | SEGMENT_D0 | SEGMENT_B8, direction), 0xFFFF, 0);
			break;
		case 3:
			metal_a_supports_paint_setup(4, 4, -1, height, RCT2_GLOBAL(0x00F4419C, uint32));
			paint_util_set_segment_support_height(paint_util_rotate_segments(SEGMENT_C8 | SEGMENT_C4 | SEGMENT_D4 | SEGMENT_C0, direction), 0xFFFF, 0);
			break;
	}

	paint_util_set_general_support_height(height + 32, 0x20);
}

static const uint8 right_quarter_turn_3_tiles_to_left_turn_map[] = {3, 1, 2, 0};

/** rct2: 0x0088AD98 */
static void paint_monorail_cycles_track_right_quarter_turn_3_tiles(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
	trackSequence = right_quarter_turn_3_tiles_to_left_turn_map[trackSequence];
	paint_monorail_cycles_track_left_quarter_turn_3_tiles(rideIndex, trackSequence, (direction + 3) % 4, height, mapElement);
}

/** rct2: 0x*/
static void paint_monorail_cycles_track_left_quarter_turn_5_tiles(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
}

/** rct2: 0x*/
static void paint_monorail_cycles_track_right_quarter_turn_5_tiles(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
}

/** rct2: 0x*/
static void paint_monorail_cycles_track_s_bend_left(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
}

/** rct2: 0x*/
static void paint_monorail_cycles_track_s_bend_right(uint8 rideIndex, uint8 trackSequence, uint8 direction, int height, rct_map_element * mapElement)
{
}

/**
 * rct2: 0x0088ac88
 */
TRACK_PAINT_FUNCTION get_track_paint_function_monorail_cycles(int trackType, int direction) {
	switch(trackType) {
		case TRACK_ELEM_FLAT:
			return paint_monorail_cycles_track_flat;

		case TRACK_ELEM_END_STATION:
		case TRACK_ELEM_BEGIN_STATION:
		case TRACK_ELEM_MIDDLE_STATION:
			return paint_monorail_cycles_station;

		case TRACK_ELEM_LEFT_QUARTER_TURN_5_TILES:
			return paint_monorail_cycles_track_left_quarter_turn_5_tiles;
		case TRACK_ELEM_RIGHT_QUARTER_TURN_5_TILES:
			return paint_monorail_cycles_track_right_quarter_turn_5_tiles;

		case TRACK_ELEM_S_BEND_LEFT:
			return paint_monorail_cycles_track_s_bend_left;
		case TRACK_ELEM_S_BEND_RIGHT:
			return paint_monorail_cycles_track_s_bend_right;

		case TRACK_ELEM_LEFT_QUARTER_TURN_3_TILES:
			return paint_monorail_cycles_track_left_quarter_turn_3_tiles;
		case TRACK_ELEM_RIGHT_QUARTER_TURN_3_TILES:
			return paint_monorail_cycles_track_right_quarter_turn_3_tiles;
	}

	return NULL;
}
