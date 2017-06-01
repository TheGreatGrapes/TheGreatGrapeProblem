#include "particlesystem.h"

ParticleSystem::ParticleSystem()
{
}

void ParticleSystem::addParticle()
{
    float r = (float)rand() / RAND_MAX;
    float x = rand() % 100 - 50;
    float y = rand() % 100 - 50;
    if (r >= 0.2){
        particles.push_back(new Particle(x, y, 1));
    }else{
        particles.push_back(new Confetti(x, y, 2));
    }
}


void ParticleSystem::run(){
    std::vector<Particle*>::iterator it;
    for(it = particles.begin(); it < particles.end(); it++){
        (*it)->update();
        if((*it)->isDead()){
            particles.erase(it);
        }
    }
}

void ParticleSystem::applyForce(Pvector* gravity){
    std::vector<Particle*>::iterator it;
    for(it = particles.begin(); it < particles.end(); it++){
        (*it)->applyForce(gravity);
    }
}


void ParticleSystem::applyRepeller(Repeller* r){
    std::vector<Particle*>::iterator it;
    for(it = particles.begin(); it < particles.end(); it++){
        Pvector* force = r->repel((*it));
        (*it)->applyForce(force);
    }
}
