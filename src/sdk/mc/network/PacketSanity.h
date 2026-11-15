#pragma once

// Drift registry over the packet id space MinecraftPacketIds defines. Diagnostic only: check() classifies, warns
// once per offending id and never drops, throws or blocks; the summary fires by itself once 500 packets were seen.
struct PacketSanity {
    enum class Verdict { Ok, Unknown, Suspicious };
    // Ok: id inside the known space, size plausible. Unknown: id outside it (protocol drift after a game update).
    // Suspicious: known id, implausible size. `data` is not consulted: the verdicts ride on id and size, and the
    // buffer pointer stays in the signature for a wire-level heuristic once a hook sees real bytes.
    static Verdict check(uint32_t id, const void* data, size_t size);
    // "[net] packet sanity: N ok, U unknown ids, S suspicious (T packets)", once per process.
    static void reportOnce();
};
