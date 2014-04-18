#ifndef IUPDATEABLE_H
#define IUPDATEABLE_H

namespace csmeg
{
class CGameTime;

class IUpdateable
{
public:
    virtual void Update(const CGameTime& gameTime) = 0;
    virtual void OnUpdate(const CGameTime& gameTime) = 0;
};

} // namespace csmeg

#endif // IUPDATEABLE_H
