# Batching Policy

> What is the optimal allocation of batches and scheduling of sequences such
> that several requests coming together are processed by a neural machine
> translation inference system minimizes latency (wait between requests) and
> maximizes throughput (minimize padding wastage/maximize efficiency)?

The sources here provides the ability to test batching-algorithms before
induction into [bergamot-translator](https://github.com/browsermt/bergamot-translator).
Implementation here makes everything dummy (Translation) or controllable
(Request parameters: priority, length, variations).

Provides a test-app with configurable parameters of number of requests,
lengths, mini-batch-words etc. 

For purposes here translation of a single batch is expected to be constant time
O(1). The objective is to compare and test batching-policy algorithms (which
are heuristic tryouts). However there are a few desirable properties, and
demand of of performance guarantees, in the average case at least.


