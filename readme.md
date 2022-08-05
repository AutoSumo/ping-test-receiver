# Ping Test Receiver

A receiver for ping tests. Runs on the ESP32 to experiment with reducing communication latency.

Ping test sender can be found at <https://github.com/AutoSumo/ping-test-sender>

The configuration that yielded the best results was:
 - websockets over wifi
 - running on the second core
 - wifi power saving disabled

This configuration was selected for stability, latency, and convenience.

Changing the CPU frequency did not yield a significant difference in latency.