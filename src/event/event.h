typedef enum {
    EVENT_KEY_PRESS,
    EVENT_MOUSE_CLICK,
    EVENT_WINDOW_RESIZE,
    // Add more event types as needed
} EventType;

typedef struct {
    EventType type;
    union {
        struct { int keycode; } keyPress;
        struct { int x, y; } mouseClick;
        struct { int width, height; } windowResize;
        // Add more event data as needed
    } data;
} Event;
