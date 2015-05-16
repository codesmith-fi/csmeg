#pragma once

#include <TVector2.h>
#include <glm/gtc/type_ptr.hpp>

namespace csmeg
{
    namespace renderer
    {
        class TCamera2D
        {
        public:
            TCamera2D();
            TCamera2D(const TVector2& pos);
            TCamera2D(const TVector2& pos, const TVector2& origin);
            TCamera2D(const TVector2& pos, const TVector2& origin, float rotation, float scale);
            virtual ~TCamera2D();

            glm::mat4 get() const;
            
            void rotate(float angle);
            void move(const TVector2& delta);
            void scale(float delta);

            void setScale(float newScale);
            void setPosition(const TVector2& newPosition);
            void setOrigin(const TVector2& newOrigin);
            void setRotation(float newRotation);

        private:
            void update();
        private: 
            TVector2 m_origin;
            TVector2 m_position;
            float m_rotation;
            float m_scale;
            glm::mat4 m_camMatrix;
        };
    }
}
