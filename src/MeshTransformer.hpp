#pragma once

#include "Mesh.hpp"

#include <hyprland/src/render/transformer/Transformer.hpp>
#include <hyprland/src/desktop/DesktopTypes.hpp>

#include <vector>

namespace OmarchyFX {

    // Renders the window's offscreen framebuffer through the deformed lattice.
    // It knows nothing about which effect deformed it — only about SMeshState.
    class CMeshTransformer : public Render::IWindowTransformer {
      public:
        CMeshTransformer(SP<SMeshState> state);
        virtual ~CMeshTransformer();

        Render::SWindowTransformBuffer transform(Render::CRenderContext& ctx, const Render::SWindowTransformBuffer& in, const Render::SWindowTransformContext& context) override;
        bool active() const override;
        CBox transformedExtents(const CBox& currentBox) const override;
        CBox sourceBoxForOutput(const CBox& outputBox, const CBox& inputBox) const override;

        static void                      dropProgram();

      private:
        bool                  ensureProgram();

        SP<SMeshState>        m_state;

        // Window bounding box for this frame, monitor-local and unscaled, as
        // handed to us right before the transformed pass is submitted.
        CBox                  m_currentBox;

        std::vector<float>    m_verts; // x, y, u, v per vertex
        std::vector<Vector2D> m_grid;
    };
}
