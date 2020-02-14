using System;
using UnityEngine;

namespace getReal3D {
    [Serializable]
    public class NavigationHelper : System.Object {

        private Transform m_transform = null;
        private CharacterController m_controller = null;
        private CharacterMotorC m_motor = null;
        private Vector3 m_lastGroundedPosition = Vector3.zero;
        private Vector3 m_initialWand = Vector3.zero;
        private Quaternion m_initialWandRotation = new Quaternion();
        private Quaternion m_initialRotation = new Quaternion();

        [Tooltip("Maximum speed of motion in m/s.")]
        public float TranslationSpeed = 1.0f;

        [Tooltip("The maximum rotation speed in degree/s")]
        public float RotationSpeed = 30.0f;

        [Tooltip("If the wand's orientation is within DeadZone degrees of its initial, do not apply the difference.")]
        public float WandLookDeadZone = 5f;

        public enum NavFollows { Wand, Head, Reference };

        [Tooltip("The navigation reference frame. If set to Reference, then the reference transform can be set.")]
        public NavFollows navFollows = NavFollows.Wand;

        [Tooltip("Reference frame.")]
        public Transform navReference = null;

        [Tooltip("Enumeration selecting the Transform defining frame of the rotation: Head, Wand, Reference. If set to Reference, then the reference transform can be set.")]
        public NavFollows rotationAround = NavFollows.Head;

        [Tooltip("Reference frame.")]
        public Transform rotationAroundReference = null;

        [Tooltip("Enumeration selecting the Transform at the center of the applied rotation: Head, Wand, Reference. If set to Reference, then the reference transform can be set.")]
        public NavFollows rotationFollows = NavFollows.Wand;

        [Tooltip("Reference frame.")]
        public Transform rotationFollowsReference = null;

        public enum RotationAxes { JoyX = 0, JoyY, JoyXY, JoyZ, JoyXZ, JoyYZ }

        [Tooltip("The axes updated by JoyLook rotation.")]
        public RotationAxes joylookRotationAxes = RotationAxes.JoyXY;
        public enum WandAxes { WandX = 0, WandY, WandXY, WandZ, WandXZ, WandYZ, WandXYZ }

        [Tooltip("The axes updated by WandLook rotation.")]
        public WandAxes wandlookRotation = WandAxes.WandY;

        [Tooltip("If enabled, apply the relative orientation difference (current – initial) of the wand continuously. If not enabled, the orientation changes only if the wand orientation changes.")]
        public bool wandLookContinuousDrive = false;

        private PlayerInputs m_inputs;
        public PlayerInputs playerInputs {
            set { m_inputs = value; }
        }

        public enum NavigationMethod {
            WalkThrough,
            AimAndGo,
            WandDrive
        }

        [Tooltip("The navigation type used (can be changed at runtime).")]
        public NavigationMethod m_navigationMethod = NavigationMethod.WalkThrough;

        public void Update(Transform transform)
        {
            ReadSettings();
            if(m_inputs == null) {
                return;
            }
            Sensor wand = m_inputs.Wand;
            Sensor head = m_inputs.Head;
            if(transform != m_transform) {
                SetTransform(transform);
            }
            switch(m_navigationMethod) {
            case NavigationMethod.WalkThrough:
                DoWalkThrough(wand, head);
                break;
            case NavigationMethod.AimAndGo:
                DoAimAndGo(wand, head);
                break;
            case NavigationMethod.WandDrive:
                DoWandDrive(wand, head);
                break;
            }

            DoJoyLook(wand, head);
            DoWandLook(wand, head);

            if(m_inputs.ResetButtonDown) {
                DoReset();
            }
        }

        private void UpdateWandLookRotation(Transform transform, Sensor wand, Sensor head,
            Quaternion initialWand, Quaternion currentWand)
        {
            Quaternion diffOrn = Quaternion.Inverse(initialWand) * currentWand;
            diffOrn = wand.rotation * diffOrn * Quaternion.Inverse(wand.rotation);
            diffOrn = head.rotation * diffOrn * Quaternion.Inverse(head.rotation);
            float angle;
            Vector3 axis;
            diffOrn.ToAngleAxis(out angle, out axis);
            float sign = angle < 0 ? -1f : 1f;
            angle = Mathf.Abs(angle);

            if(angle < WandLookDeadZone) return;
            if(wandLookContinuousDrive) {
                angle = Mathf.Clamp01((angle - WandLookDeadZone) /
                    (RotationSpeed - WandLookDeadZone)) * RotationSpeed;
                diffOrn = Quaternion.AngleAxis(sign * angle, axis);
            }
            switch(wandlookRotation) {
            case WandAxes.WandX: diffOrn = Quaternion.Euler
                    (new Vector3(diffOrn.eulerAngles.x, 0, 0)); break;
            case WandAxes.WandY: diffOrn = Quaternion.Euler
                    (new Vector3(0, diffOrn.eulerAngles.y, 0)); break;
            case WandAxes.WandXY: diffOrn = Quaternion.Euler
                    (new Vector3(diffOrn.eulerAngles.x, diffOrn.eulerAngles.y, 0)); break;
            case WandAxes.WandZ: diffOrn = Quaternion.Euler
                    (new Vector3(0, 0, diffOrn.eulerAngles.z)); break;
            case WandAxes.WandXZ: diffOrn = Quaternion.Euler
                    (new Vector3(diffOrn.eulerAngles.x, 0, diffOrn.eulerAngles.z)); break;
            case WandAxes.WandYZ: diffOrn = Quaternion.Euler
                    (new Vector3(0, diffOrn.eulerAngles.y, diffOrn.eulerAngles.z)); break;
            case WandAxes.WandXYZ: break;
            }
            Vector3 up = m_transform.up;
            Vector3 forward = head.rotation * Vector3.forward;
            Vector3 right = Vector3.Cross(forward, up);
            forward = Vector3.Cross(right, up);
            Quaternion frame = Quaternion.LookRotation(forward, up);
            diffOrn = Quaternion.Inverse(frame) * diffOrn * frame;
            Vector3 about = m_transform.position;
            switch(rotationAround) {
            case NavFollows.Head: about =
                    m_transform.localToWorldMatrix.MultiplyPoint3x4(head.position); break;
            case NavFollows.Wand: about =
                    m_transform.localToWorldMatrix.MultiplyPoint3x4(wand.position); break;
            case NavFollows.Reference: if(rotationAroundReference != null)
                    about = rotationAroundReference.position; break;
            }
            about = m_transform.worldToLocalMatrix * (about - m_transform.position);
            if(m_controller == null || !m_controller.enabled)
                m_transform.Translate(about, Space.Self);
            if(wandLookContinuousDrive) {
                m_transform.rotation = Quaternion.Slerp
                    (m_initialRotation, m_initialRotation * diffOrn, Time.smoothDeltaTime);
                m_initialRotation = m_transform.rotation;
            }
            else {
                m_transform.rotation = m_initialRotation * diffOrn;
            }
            if(m_controller == null || !m_controller.enabled)
                m_transform.Translate(-about, Space.Self);
        }

        public void FixedUpdate(Transform transform)
        {

        }

        private void DoJoyLook(Sensor wand, Sensor head)
        {
            Vector2 joy = new Vector2(m_inputs.YawAxis, m_inputs.PitchAxis);
            if(joy.sqrMagnitude > 0f) {
                UpdateRotation(joy, wand, head, Time.smoothDeltaTime);
            }
        }

        private void DoWandLook(Sensor wand, Sensor head)
        {
            if(m_inputs.WandLookButtonDown) {
                m_initialWandRotation = wand.rotation;
                m_initialRotation = m_transform.rotation;
            }
            else if(m_inputs.WandLookButton) {
                UpdateWandLookRotation(m_transform, wand, head, m_initialWandRotation,
                    wand.rotation);
            }
        }

        private void SetTransform(Transform transform)
        {
            m_transform = transform;
            m_controller = transform.GetComponent<CharacterController>();
            m_motor = transform.GetComponent<CharacterMotorC>();
        }

        private void DoWandDrive(Sensor wand, Sensor head)
        {
            if(m_inputs.WandDriveButtonDown) {
                m_initialWand = wand.position;
            }
            else if(m_inputs.WandDriveButtonUp) {
                m_initialWand = Vector3.zero;
                if(m_motor != null) {
                    m_motor.inputMoveDirection = Vector3.zero;
                    m_motor.inputJump = false;
                }
            }
            else if(m_inputs.WandDriveButton) {
                Vector3 directionVector = wand.position - m_initialWand;
                directionVector = m_transform.TransformDirection(directionVector);
                directionVector -= Vector3.Dot(directionVector, Physics.gravity.normalized) *
                    Physics.gravity.normalized;

                DoWalk(directionVector);
            }
        }

        private void DoAimAndGo(Sensor wand, Sensor head)
        {
            EnsureBehaviourEnabled(m_controller, true);
            EnsureBehaviourEnabled(m_motor, false);

            Vector3 joy = new Vector3(m_inputs.StrafeAxis, 0, m_inputs.ForwardAxis);

            float elapsed = Time.smoothDeltaTime;

            // Get the input vector from keyboard or analog stick
            Vector3 directionVector = joy;
            switch(navFollows) {
            case NavFollows.Wand:
                directionVector = wand.rotation * directionVector;
                break;
            case NavFollows.Head:
                directionVector = head.rotation * directionVector;
                break;
            case NavFollows.Reference:
                if(navReference != null)
                    directionVector = (navReference.localToWorldMatrix *
                        m_transform.worldToLocalMatrix).MultiplyVector(directionVector);
                break;
            }

            if(directionVector != Vector3.zero) {
                // Get the length of the directon vector and then normalize it
                // Dividing by the length is cheaper than normalizing when we already have
                // the length anyway
                float directionLength = directionVector.magnitude;
                directionVector = directionVector / directionLength;

                // Make sure the length is no bigger than 1
                directionLength = Mathf.Min(1, directionLength);

                // Make the input vector more sensitive towards the extremes and less sensitive in
                // the middle
                // This makes it easier to control slow speeds when using analog sticks
                directionLength = directionLength * directionLength;

                // Multiply the normalized direction vector by the modified length
                directionVector = directionVector * directionLength;
            }

            directionVector *= TranslationSpeed;
            if(!m_inputs.NavSpeedButton) {
                directionVector *= Scale.worldScale;
            }

            // Move the controller
            if(m_controller != null && m_controller.enabled) {
                CollisionFlags flags = m_controller.Move
                    (m_transform.TransformDirection(directionVector) * elapsed);
                bool grounded = (flags & CollisionFlags.CollidedBelow) != 0;
                if(grounded) m_lastGroundedPosition = m_transform.position;
            }
            else {
                m_transform.position += m_transform.TransformDirection(directionVector) * elapsed;
            }
        }

        private void DoReset()
        {
            m_transform.position = m_lastGroundedPosition;
            Vector3 up = -Physics.gravity;
            up = (up.sqrMagnitude == 0.0f) ? Vector3.up : up.normalized;
            up.Scale(m_transform.eulerAngles);
            m_transform.rotation = Quaternion.Euler(up);
        }

        private void DoWalkThrough(Sensor wand, Sensor head)
        {
            EnsureBehaviourEnabled(m_controller, true);
            EnsureBehaviourEnabled(m_motor, true);

            Vector3 joy = new Vector3(m_inputs.StrafeAxis, 0, m_inputs.ForwardAxis);

            float elapsed = Time.smoothDeltaTime;

            // Get the input vector from keyboard or analog stick
            Vector3 directionVector = joy;
            switch(navFollows) {
            case NavFollows.Wand:
                directionVector = wand.rotation * directionVector;
                break;
            case NavFollows.Head:
                directionVector = head.rotation * directionVector;
                break;
            case NavFollows.Reference:
                if(navReference != null)
                    directionVector = (navReference.localToWorldMatrix *
                        m_transform.worldToLocalMatrix).MultiplyVector(directionVector);
                break;
            }

            DoWalk(directionVector);
        }

        private void DoWalk(Vector3 directionVector)
        {
            float elapsed = Time.smoothDeltaTime;

            if(directionVector != Vector3.zero) {
                // Get the length of the direction vector and then normalize it
                // Dividing by the length is cheaper than normalizing when we already have the
                // length anyway
                float directionLength = directionVector.magnitude;
                directionVector = directionVector / directionLength;

                // Make sure the length is no bigger than 1
                directionLength = Mathf.Min(1, directionLength);

                // Make the input vector more sensitive towards the extremes and less sensitive in
                // the middle
                // This makes it easier to control slow speeds when using analog sticks
                directionLength = directionLength * directionLength;

                // Multiply the normalized direction vector by the modified length
                directionVector = directionVector * directionLength;
            }

            directionVector *= TranslationSpeed;
            if(!m_inputs.NavSpeedButton)
                directionVector *= Scale.worldScale;

            // Apply the direction to the CharacterMotor, CharacterController, or Transform, as
            // available
            if(m_motor != null && m_motor.enabled && m_motor.canControl) {
                m_motor.inputMoveDirection = m_transform.rotation * directionVector;
                m_motor.inputJump = m_inputs.JumpButtonDown;
            }
            else if(m_controller != null && m_controller.enabled) {
                CollisionFlags flags = m_controller.Move
                    (m_transform.TransformDirection(directionVector) * elapsed);
                bool grounded = (flags & CollisionFlags.CollidedBelow) != 0;
                if(grounded) m_lastGroundedPosition = m_transform.position;
            }
            else {
                m_transform.position += m_transform.TransformDirection(directionVector) * elapsed;
            }
        }

        private void EnsureBehaviourEnabled(MonoBehaviour behaviour, bool enabled)
        {
            if(behaviour && behaviour.enabled != enabled) {
                behaviour.enabled = enabled;
            }
        }

        private void EnsureBehaviourEnabled(CharacterController behaviour, bool enabled)
        {
            if(behaviour && behaviour.enabled != enabled) {
                behaviour.enabled = enabled;
            }
        }

        private void WriteSettingIfMissing(string name, float value)
        {
            if(!getReal3D.Input.NavOptions.HasValue(name)) {
                getReal3D.Input.NavOptions.SetValue<float>(name, value);
            }
        }
        public void WriteSettings()
        {

            WriteSettingIfMissing("TranslationSpeed", TranslationSpeed);
            WriteSettingIfMissing("RotationSpeed", RotationSpeed);
            WriteSettingIfMissing("WandLookDeadZone", WandLookDeadZone);
        }

        public void ReadSettings()
        {
            getReal3D.Input.NavOptions.GetValue<float>("RotationSpeed", ref RotationSpeed);
            getReal3D.Input.NavOptions.GetValue<float>("TranslationSpeed", ref TranslationSpeed);
            getReal3D.Input.NavOptions.GetValue<float>("WandLookDeadZone", ref WandLookDeadZone);
        }

        private void UpdateRotation(Vector2 joy, Sensor wand, Sensor head, float elapsed)
        {

            joy *= RotationSpeed * elapsed; // default scale ~6 seconds to spin 360 degrees

            Matrix4x4 frame = Matrix4x4.identity;
            switch(rotationFollows) {
            case NavFollows.Head: frame = Matrix4x4.TRS(Vector3.zero, m_transform.rotation *
                head.rotation, Vector3.one); break;
            case NavFollows.Wand: frame = Matrix4x4.TRS(Vector3.zero, m_transform.rotation *
                wand.rotation, Vector3.one); break;
            case NavFollows.Reference:
                frame = (rotationFollowsReference != null)
                      ? Matrix4x4.TRS(Vector3.zero, rotationFollowsReference.rotation, Vector3.one)
                      : Matrix4x4.TRS(Vector3.zero, m_transform.rotation, Vector3.one); break;
            }

            Vector3 up = -Physics.gravity;
            up = (up.sqrMagnitude == 0.0f) ? Vector3.up : up.normalized;
            Vector3 forward = frame.GetColumn(2);
            Vector3 right = frame.GetColumn(0);

            Vector3 about = m_transform.position;
            switch(rotationAround) {
            case NavFollows.Head: about = m_transform.localToWorldMatrix.
                    MultiplyPoint3x4(head.position); break;
            case NavFollows.Wand: about = m_transform.localToWorldMatrix.
                    MultiplyPoint3x4(wand.position); break;
            case NavFollows.Reference: if(rotationAroundReference != null)
                    about = rotationAroundReference.position; break;
            }
            about = m_transform.worldToLocalMatrix * (about - m_transform.position);
            if(m_controller == null || !m_controller.enabled) {
                m_transform.Translate(about, Space.Self);
            }

            switch(joylookRotationAxes) {
            case RotationAxes.JoyX: m_transform.Rotate(right, joy.x, Space.World); break;
            case RotationAxes.JoyY: m_transform.Rotate(up, joy.x, Space.World); break;
            case RotationAxes.JoyZ: m_transform.Rotate(forward, joy.x, Space.World); break;
            case RotationAxes.JoyXY: m_transform.Rotate(up, joy.x, Space.World);
                m_transform.Rotate(right, joy.y, Space.World); break;
            case RotationAxes.JoyXZ: m_transform.Rotate(forward, joy.x, Space.World);
                m_transform.Rotate(right, joy.y, Space.World); break;
            case RotationAxes.JoyYZ: m_transform.Rotate(up, joy.x, Space.World);
                m_transform.Rotate(forward, joy.y, Space.World); break;
            }

            if(m_controller == null || !m_controller.enabled) {
                m_transform.Translate(-about, Space.Self);
            }
        }

    }

    public interface NavigationScriptInterface
    {
        NavigationHelper navigationHelper { get; }
    }
}
