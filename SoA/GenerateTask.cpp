#include "stdafx.h"
#include "GenerateTask.h"

#include "Chunk.h"
#include "ChunkGenerator.h"

void GenerateTask::execute(WorkerData* workerData) {
    Chunk& chunk = query->chunk;

    // Check if this is a heightmap gen
    if (chunk.gridData->isLoading) {
        chunkGenerator->m_proceduralGenerator.generateHeightmap(&chunk, heightData);
    } else { // Its a chunk gen

        switch (query->genLevel) {
            case ChunkGenLevel::GEN_DONE:
            case ChunkGenLevel::GEN_TERRAIN:
                chunkGenerator->m_proceduralGenerator.generateChunk(&chunk, heightData);
                chunk.genLevel = ChunkGenLevel::GEN_DONE;
                break;
            case ChunkGenLevel::GEN_FLORA:
                chunk.genLevel = ChunkGenLevel::GEN_DONE;
                break;
            case ChunkGenLevel::GEN_SCRIPT:
                chunk.genLevel = ChunkGenLevel::GEN_DONE;
                break;
        }
        query->m_isFinished = true;
        query->m_cond.notify_one();
        // TODO(Ben): Not true for all gen?
        chunk.isAccessible = true;
    }
    chunkGenerator->finishQuery(query);
}
