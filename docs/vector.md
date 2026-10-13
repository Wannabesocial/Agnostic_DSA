# Generic Vector Data Structure

## Algorithmic Complexity (Big-O Analysis)
| Category | Function | Time Complexity | Space Complexity | Description / Notes |
| :--- | :--- | :--- | :--- | :--- |
| **Constructors** | `vector_create_default()` | $O(1)$ | $O(1)$ | Allocates header &amp; default capacity buffer ($n=8$). |
| | `vector_create_reserve()` | $O(1)$ | $O(n)$ | Allocates buffer for $n$ elements. With $1 \leq n \leq$ `SIZE_MAX`. |
| **Destructors** | `vector_destroy()` | $O(1)$ | $O(1)$ | Frees internal buffer and vector struct. |
| **Modifiers** | `vector_push_back()` | $O(1)$ / $O(n)$ | $O(1)$ / $O(n)$ | $O(n)$ occurs only during `growth`, when `capacity` and `size` are equel. |
| | `vector_pop_back()` | $O(1)$ | $O(1)$ | Removes last element (optional output copy). |
| | `vector_insert()` | $O(1)$ (last element) / $O(n)$ | $O(1)$ / $O(n)$ (need `growth`) | Shifts elements to the right using `memmove`. |
| | `vector_erase()` | $O(1)$ (last element) / $O(n)$ | $O(1)$ | Shifts elements to the left using `memmove`. |
| | `vector_resize()` | $O(1)$ / $O(n)$ (need `growth`) | $O(1)$ / $O(n)$ (need `growth`) | Reallocates buffer if new size exceeds capacity. |
| **Capacity** | `vector_reserve()` | $O(1)$ / $O(n)$ (realloc) | $O(1)$ / $O(n)$ (realloc) | Change the Capacity of the Vector to new one, pre-allocates memory |
| | `vector_shrink_to_fit()`| $O(n)$ | $O(n)$ | Shrinks capacity to match current length. |
| | `vector_size()` / `capacity()` / `empty()` | $O(1)$ | $O(1)$ | Direct variable access. |
| **Element Access** | `vector_at()` | $O(1)$ | $O(1)$ | Direct pointer arithmetic with bounds check. |
| | `vector_data()` | $O(1)$ | $O(1)$ | Returns base pointer (enables pointer arithmetic). |
| | `vector_back()` | $O(1)$ | $O(1)$ | Returns pointer to last element. |


## Code Example
```c
#include <stdio.h>
#include "vector.h"

typedef struct {
    int x;
    int y;
} Point2D;

int main(void)
{
    Vector *v = NULL;

    // Create vector for Point2D elements
    if(vector_create_default(&v, sizeof(Point2D)) != VECTOR_SUCCESS){
        printf("Failed to initialize vector\n");
        return 1;
    }

    // Push elements
    Point2D p1 = {10, 20};
    Point2D p2 = {30, 40};
    vector_push_back(v, &p1);
    vector_push_back(v, &p2);

    // Access element
    Point2D *retrieved = (Point2D *)vector_at(v, 0);
    if (retrieved != NULL){
        printf("Point 0: (%d, %d)\n", retrieved->x, retrieved->y);
    }

    // Direct iteration using pointer arithmetic via vector_data()
    Point2D *ptr = (Point2D *)vector_data(v);
    size_t len = vector_size(v);
    for (size_t i = 0; i < len; i++){
        printf("Element %d: (%d, %d)\n", i, ptr[i].x, ptr[i].y);
    }

    // Clean up
    vector_destroy(v);
    return 0;
}
```