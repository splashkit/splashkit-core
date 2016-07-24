//
//  images.hpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef images_hpp
#define images_hpp

/// The bitmap type is a pointer to a BitmapData. The BitmapData record
/// contains the data used by the SwinGame API to represent
/// bitmaps. You can create new bitmaps in memory for drawing operatings
/// using the `CreateBitmap` function. This can then be optimised for drawing
/// to the screen using the `OptimiseBitmap` routine. Also see the `DrawBitmap`
/// routines.
///
/// @class Bitmap
/// @pointer_wrapper
/// @field pointer: pointer
typedef struct _bitmap_data *bitmap;


#endif /* images_hpp */
