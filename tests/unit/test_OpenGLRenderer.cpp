#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../src/renderer/OpenGLRenderer.cpp"

class MockRigidbody : public SphericRigidbody {
public:
  MockRigidbody(double r, double m) : SphericRigidbody(r,m){
  }
    MOCK_METHOD(boost::numeric::ublas::vector<double>, getPosition, (), (const, override));
};

class OpenGLRendererTest : public ::testing::Test {
protected:
    OpenGLRenderer renderer;

    void SetUp() override {
        // Initialize the renderer
        renderer.initialize();
    }

    void TearDown() override {
        // Clean up the renderer
        renderer.cleanup();
    }
};

TEST_F(OpenGLRendererTest, Initialization) {
    ASSERT_NE(renderer.window, nullptr) << "Window should be initialized";
}

TEST_F(OpenGLRendererTest, Cleanup) {
    renderer.cleanup();
    ASSERT_EQ(renderer.window, nullptr) << "Window should be nullptr after cleanup";
}

TEST_F(OpenGLRendererTest, RenderCallRigidbody) {
    MockRigidbody mockRigidbody(10.0, 10.0);
    boost::numeric::ublas::vector<double> position(2);
    position(0) = 0.0;
    position(1) = 0.0;
    EXPECT_CALL(mockRigidbody, getPosition()).WillOnce(::testing::Return(position));

    renderer.render(mockRigidbody);
    // Since rendering is visual, we can't assert on the output, but we can ensure no crashes occur
}
