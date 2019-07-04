#ifndef wrapper_hpp
#define wrapper_hpp

#ifdef __cplusplus
extern "C" {
#endif

typedef enum ClipType
{
    ctIntersection,
    ctUnion,
    ctDifference,
    ctXor
} ClipType;

typedef enum PolyType
{
    ptSubject,
    ptClip
} PolyType;

typedef enum PolyFillType
{
    pftEvenOdd,
    pftNonZero,
    pftPositive,
    pftNegative
} PolyFillType;

#ifdef use_int32
typedef int cInt;
static cInt const loRange = 0x7FFF;
static cInt const hiRange = 0x7FFF;
#else
typedef signed long long cInt;
static cInt const loRange = 0x3FFFFFFF;
static cInt const hiRange = 0x3FFFFFFFFFFFFFFFLL;
typedef signed long long long64; // used by Int128 class
typedef unsigned long long ulong64;
#endif

typedef cInt Vertice[2];

typedef struct Path
{
    Vertice* vertices;
    int vertices_count;
    int closed;
} Path;

typedef struct Polygon
{
    Path* paths;
    int paths_count;
    PolyType type;
} Polygon;

typedef struct Polygons
{
    Polygon* polygons;
    int polygons_count;
} Polygons;

Polygons execute(
    ClipType clip_type,
    Polygons polygons,
    PolyFillType subject_fill_type,
    PolyFillType clip_fill_type);

void free_path(Path path);
void free_polygon(Polygon polygon);
void free_polygons(Polygons polygons);

#ifdef __cplusplus
}
#endif

#endif // clipper_hpp
